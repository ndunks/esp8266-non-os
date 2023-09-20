
ESPTOOL ?= /home/rifin/app/ESP8266_RTOS_SDK/components/esptool_py/esptool/esptool.py
IDFMONITOR ?= /home/rifin/app/ESP8266_RTOS_SDK/tools/idf_monitor.py
DEV ?= /dev/ttyUSB0

CC = xtensa-lx106-elf-gcc
SIZE = xtensa-lx106-elf-size
CFLAGS = -I./include -Os -g  -mlongcalls -Wall -Werror -mtext-section-literals
LDFLAGS = -L./ld \
	-nostdlib \
	-Wl,-EL \
	-u main \
    -mlongcalls \
    -mtext-section-literals \
    -Wl,--no-check-sections \
    -Wl,--gc-sections	\
    -Wl,-static \
	-Tmain.ld


SRC_DIR		:= src
BUILD_DIR   := build

TARGET_ELF  = $(BUILD_DIR)/app.elf
TARGET_BIN  = $(BUILD_DIR)/app.bin
SRC	     	= $(wildcard $(SRC_DIR)/*.c)
OBJ	     	= $(patsubst %.c,$(BUILD_DIR)/%.o,$(subst $(SRC_DIR)/,,$(SRC)))

.PHONY: all clean qemulate flash monitor

all: $(TARGET_ELF)

$(TARGET_ELF): $(OBJ)
	@echo "Linking $^"
	$(CC) $(LDFLAGS) -o $@ $^
#	nm -S -n $(@) > image.map

$(TARGET_BIN): $(TARGET_ELF)
	$(SIZE) $<
	$(ESPTOOL) elf2image $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $^"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

qemulate: $(TARGET_ELF)
	qemu-system-xtensa -M esp8266 -nographic -serial stdio -monitor none -kernel $(TARGET_ELF)

clean:
	rm -rf $(BUILD_DIR)

flash: $(TARGET_BIN)
	$(ESPTOOL) --chip esp8266 --port "/dev/ttyUSB0" --baud 2000000 \
		--before "default_reset" --after "hard_reset" write_flash -z  \
		--flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $<

monitor:
	$(IDFMONITOR) -b 74880 -p $(DEV) $(TARGET_ELF)