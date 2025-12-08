#include <stdint.h>

static volatile uint32_t g_tick = 0;    // contor global de tick

// incrementeaza contorul global de tick
void rtos_tick_inc(){
    g_tick++;
}

// returneaza valoarea curenta a tick-ului
uint32_t rtos_now(){
    return g_tick;
}