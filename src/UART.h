#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_gpio.h"
#include <string.h>
#include <stdio.h>


UART_HandleTypeDef huart2;
static void MX_USART2_UART_Init(void);
void print_uart(char *msg);
char* scan_uart(void);

static void MX_USART2_UART_Init(void){
	huart2.Instance=USART2;
	huart2.Init.BaudRate=9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits= UART_STOPBITS_1;
	huart2.Init.Parity= UART_PARITY_NONE;
	huart2.Init.Mode= UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl= UART_HWCONTROL_NONE;
	HAL_UART_Init(&huart2);
}

void print_uart(char *msg){
	char mess[128];
	sprintf(mess,"%s\n\r",msg);
	HAL_UART_Transmit(&huart2,(uint8_t*)mess,strlen(mess),0xFFFF);
}
