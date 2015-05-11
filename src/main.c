#include <stdlib.h>
#include "diag/Trace.h"
#include "UART.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

void MX_GPIO_Init(void);
void blink(void);


int blinks=1;

int main(int argc, char* argv[])
{
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	print_uart("Programma di Esempio Nucleo");
	print_uart("Avvio...");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_Delay(1500);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_Delay(1500);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET);
	print_uart("Avvio completato");
    print_uart("blink ATTIVO");

  while (1)
    {
	 // print_uart("while..");
	  if(blinks==1){
		  blink();
	  }
    }
}

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOC_CLK_ENABLE();
  __GPIOH_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __USART2_CLK_ENABLE();

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed= GPIO_SPEED_FAST;
  //Setting Interrupt
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0F, 0x00);
   HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);



  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
void blink(void){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	HAL_Delay(1000);
}
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(blinks==1){
	  print_uart("Bottone premuto");
	  print_uart("blink DISATTIVATO");
	  blinks=0;
	  }
    else{
      print_uart("Bottone premuto");
      print_uart("blink ATTIVO");
	  blinks=1;
	 }
}
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
