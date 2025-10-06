#ifndef __UART_H
#define __UART_H
#include "main.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
void delay_us(uint8_t us); 
void uart_transmit_char (uint8_t data);
void uart_transmit_string (char *str);
uint8_t uart_receive (void);
extern TIM_HandleTypeDef htim1;
#endif /* __UART_H */