#include "uart.h"
void delay_us(uint8_t us) 
{
    htim1.Instance->CNT = 0;  // reset the counter
    while (htim1.Instance->CNT < us);  // wait until the counter reaches the us input in the argument
}

void uart_transmit_char(uint8_t data){
    HAL_GPIO_WritePin(GPIOC, Transmit_Pin, 0); // start bit
    delay_us(104); 
    for(int i = 0; i < 8 ; i++ ){
        if(data & 0x01)
            HAL_GPIO_WritePin(GPIOC, Transmit_Pin,1); // send 1
        else 
            HAL_GPIO_WritePin(GPIOC, Transmit_Pin,0); // send 0
        delay_us(104);
        data = data >> 1; // shift to get the next bit
    }
    HAL_GPIO_WritePin(GPIOC, Transmit_Pin,1); // stop bit
    delay_us(104);
}

void uart_transmit_string (char *str){
    while(*str){
        uart_transmit_char(*str++);
    }
}

uint8_t uart_receive(){
	uint8_t data = 0;
	// Doi keo xuong 0 la bat dau nhan bit
	while(HAL_GPIO_ReadPin(GPIOC, Receive_Pin) == 1);
	delay_us(156);
	for(int i = 0 ; i < 8 ; i++){
		if(HAL_GPIO_ReadPin(GPIOC, Receive_Pin)==1)
			data |= (1 << i);
		delay_us(104);
	}

	return data;
}