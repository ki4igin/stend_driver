#ifndef __UART_H
#define __UART_H

#include "stm32f4xx.h"

#define UART_NBUF_RX 4

extern struct uart_rx {
    volatile uint32_t is_new_data;
    uint8_t data[UART_NBUF_RX];
} uart_rx;

void UART_Init(void);
void UART_Send_Array(void *buf, uint32_t size);

#endif
