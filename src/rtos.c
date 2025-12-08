#include "rtos.h"

// ----------------------------------------------
// Pool static de TCB-uri si stive
// ----------------------------------------------
static rtos_tcb_t tcb_pool[RTOS_MAX_TASKS];
static uint32_t tcb_count = 0;
static uint32_t task_stacks[RTOS_MAX_TASKS][RTOS_STACK_SIZE];
static rtos_tcb_t *current_task = NULL;
static volatile uint32_t g_tick = 0;

// ----------------------------------------------
// Functii pentru Tick
// ----------------------------------------------
void rtos_tick_handler(){
    g_tick++;
}

uint32_t rtos_now(){
    return g_tick;
}

// ----------------------------------------------
// Initializare RTOS
// ----------------------------------------------
void rtos_init(){
    tcb_count = 0;
    current_task = NULL;
}

// ----------------------------------------------
// Creare task (fara context switching momentan)
// ----------------------------------------------
void rtos_task_create(void (*task_fn)(void), uint32_t priority){
    if(tcb_count >= RTOS_MAX_TASKS){
        return;
    }

    rtos_tcb_t *tcb = &tcb_pool[tcb_count];
    tcb->priority = priority;
    tcb->delay_ticks = 0;

    uint32_t *stack = task_stacks[tcb_count];
    uint32_t size = RTOS_STACK_SIZE;

    stack[size - 1] = 0x01000000;           // xPSR (thumb bit = 1)
    stack[size - 2] = (uint32_t)task_fn;    // PC = functia task-ului
    stack[size - 3] = 0xFFFFFFFD;           // LR pentru thread mode cu PSP (stiva separata)
    stack[size - 4] = 0;                    // R12
    stack[size - 5] = 0;                    // R3
    stack[size - 6] = 0;                    // R2
    stack[size - 7] = 0;                    // R1
    stack[size - 8] = 0;                    // R0

    // context software (R4..R11) va fi salvat/restaurat ulterior
    tcb->stack_ptr = &stack[size - 16];
    
    tcb_count++;
}

// ----------------------------------------------
// Pornire scheduler (fara context switching momentan)
// ----------------------------------------------
void rtos_start(){
    if(tcb_count > 0){
        current_task = &tcb_pool[0];
    }
    while(1) {
        // aici va fi context switching
    }
}