#include "extint.h"
#include "stepmotor.h"
#include "extern.h"

extern uint8_t stepmotor_state;
/**
 * move from Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c to here
 * external INT callback function
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case GPIO_PIN_0: // PA0 / 1층
		if(arrive == 1) // 도착해야할 층이 1층일 때 1층에 도착한 경우
		{
			flag=1;
		}
		break;
	case GPIO_PIN_1: // PB1 / 2층
		if(arrive == 2) // 도착해야할 층이 2층일 때 2층에 도착한 경우
		{
			flag=1;
		}
		break;
	case GPIO_PIN_2: // PB2 / 3층
		if(arrive == 3) // 도착해야할 층이 3층일 때 3층에 도착한 경우
		{
			flag=1;
		}
		break;
	case GPIO_PIN_4: // PB4 / 4층
		if(arrive == 4) // 도착해야할 층이 4층일 때 4층에 도착한 경우
		{
			flag=1;
		}
		break;
	}
}





