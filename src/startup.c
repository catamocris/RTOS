#include "rtos.h"

extern uint32_t _estack;
extern uint32_t _sidata;  // start init values for .data (in FLASH)
extern uint32_t _sdata;   // start of .data in RAM
extern uint32_t _edata;   // end of .data in RAM
extern uint32_t _sbss;    // start of .bss in RAM
extern uint32_t _ebss;    // end of .bss in RAM

volatile uint32_t g_tick = 0;

void Reset_Handler();
void Default_Handler();
void SysTick_Handler();

extern int main();

// ----------------------------------------------
// Vector Table
// ----------------------------------------------
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))(&_estack),   // 0: initial stack pointer
    Reset_Handler,                // 1: Reset
    Default_Handler,              // 2: NMI
    Default_Handler,              // 3: HardFault
    Default_Handler,              // 4: MemManage
    Default_Handler,              // 5: BusFault
    Default_Handler,              // 6: UsageFault
    0, 0, 0, 0,                   // 7–10: rezervate
    Default_Handler,              // 11: SVCall
    Default_Handler,              // 12: Debug monitor
    0,                            // 13: rezervat
    Default_Handler,              // 14: PendSV
    SysTick_Handler,              // 15: SysTick
};

// ----------------------------------------------
// Handlers
// ----------------------------------------------
void Default_Handler(){
    while(1){}
}

void Reset_Handler(){
    uint32_t *src;
    uint32_t *dst;

    src = &_sidata;
    dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0u;
    }

    extern int main();
    main();

    while(1){}
}


void SysTick_Handler(){
    rtos_tick_handler();
}