#include "rtos.h"

extern uint32_t rtos_now();

// ----------------------------------------------
// SysTick
// ----------------------------------------------
#define SYST_CSR   (*(volatile uint32_t *)0xE000E010) // Control and Status
#define SYST_RVR   (*(volatile uint32_t *)0xE000E014) // Reload Value
#define SYST_CVR   (*(volatile uint32_t *)0xE000E018) // Current Value

#define SYST_CSR_ENABLE      (1u << 0)  // enable counter
#define SYST_CSR_TICKINT     (1u << 1)  // enable interrupt
#define SYST_CSR_CLKSOURCE   (1u << 2)  // 1 = core clock

static void systick_init(){
    uint32_t reload = (CPU_CLOCK_HZ / RTOS_TICK_RATE_HZ) - 1u;
    if(reload > 0x00FFFFFFu){
        while(1){}
    }

    SYST_RVR = reload;        // setam valoarea de reload
    SYST_CVR = 0u;            // resetam contorul curent
    SYST_CSR = SYST_CSR_ENABLE | SYST_CSR_TICKINT | SYST_CSR_CLKSOURCE;
}

// ----------------------------------------------
// Task-uri
// ----------------------------------------------
void task1(){
    while(1){

    }
}

// ----------------------------------------------
// Main
// ----------------------------------------------
int main(){

    systick_init();

    rtos_init();

    rtos_task_create(task1, 1);

    rtos_start();

    while(1){}
}