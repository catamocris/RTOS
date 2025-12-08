#ifndef RTOS_H
#define RTOS_H

#include <stdint.h>
#include <stddef.h>
#include "rtos_config.h"

// ----------------------------------------------
// Task Control Block
// ----------------------------------------------
typedef struct rtos_tcb{
    uint32_t *stack_ptr;    // pointer la varful stivei taskului
    uint32_t priority;      // prioritatea
    uint32_t delay_ticks;   // delay in ticks
    struct rtos_tcb *next;  // pt ready lists
}rtos_tcb_t;

// ----------------------------------------------
// API
// ----------------------------------------------
void rtos_init();
void rtos_task_create(void (*task_fn)(void), uint32_t priority);
void rtos_start();
void rtos_tick_handler();
uint32_t rtos_now();

#endif