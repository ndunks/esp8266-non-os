#include "osapi.h"
extern uint32_t _bss_start;
extern uint32_t _bss_end;
uint32_t counter = 0;
int main()
{
    // init
    uint32_t *addr;
    for (addr = &_bss_start; addr < &_bss_end; addr++) { *addr = 0; }
    while(1){
        printf("Hello world! %04x\n", counter++);
        ets_delay_us(1000000);
    }
}
