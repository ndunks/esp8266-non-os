#include "osapi.h"
#include "gpio_struct.h"
#include "pin_mux_register.h"

// Builtin LED pin on ESP8266Mod/12S by AI-Thinker
#define LED_PIN 2

static inline uint32_t soc_get_ccount(void)
{
    uint32_t ticks;

    __asm__ __volatile__(
        "rsr    %0, ccount\n"
        : "=a"(ticks)
        :
        : "memory");

    return ticks;
}

int main()
{
    int flag = 0;
    // Configure GPIO2 as IO (it have builtin LED), not as UART1
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

    // output mode
    GPIO.enable_w1ts |= (0x1 << LED_PIN);

    while (1)
    {
        // GPIO.out_w1ts + 0 = Set on
        // GPIO.out_w1ts + 1 = GPIO.out_w1tc = Clear
        *(&GPIO.out_w1ts + flag) |= 0x1 << LED_PIN;

        flag = !flag;

        // This will printed on UART0, connected with USB
        ets_printf("Tick %08x %08x\n", soc_get_ccount(), GPIO.out);
        // Clock is not configured, this is not 1 second
        ets_delay_us(1000000);
    }
}
