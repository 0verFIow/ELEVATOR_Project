#include "button.h"


void init_button(void)
{
	GPIOC->PUPDR = 0x00000055;
}



void button_led_toggle_test(void)
{
	init_button();
	// 버튼을 한 번 눌렀다 떼면 led가 toggle되도록 code를 구현
	if(get_button(GPIOC,GPIO_PIN_0, BTN0) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	}
	if(get_button(GPIOC,GPIO_PIN_1, BTN1) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}
	if(get_button(GPIOC,GPIO_PIN_2, BTN2) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	}
	if(get_button(GPIOC,GPIO_PIN_3, BTN3) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	}
	if(get_button(GPIOC,GPIO_PIN_13, BTN4) == BUTTON_PRESS) // BLUE BUTTON
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
}

int get_button(GPIO_TypeDef *GPIO,int button_pin, int button_num) //interlock & debounce 구현
{
	// 지역 변수에 static을 쓰면 전역 변수처럼 함수를 빠져 나갔다 와도 값이 유지가 된다.
	static unsigned char button_status[] = {BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE};

	int current_state;
	current_state = HAL_GPIO_ReadPin(GPIO, button_pin);

	if(current_state == BUTTON_PRESS && button_status[button_num] == BUTTON_RELEASE) //버튼이 처음 눌러진 상태
	{
		HAL_Delay(60); // noise가 지나가기를 기다린다.
		button_status[button_num] = BUTTON_PRESS; // noise가 지나간 상태의 High 상태
		return BUTTON_RELEASE; // 아직은 완전히 눌렸다 떼어진 상태가 아니다.
	}
	else if(current_state == BUTTON_RELEASE && button_status[button_num] == BUTTON_PRESS)
	{
		HAL_Delay(60);
		button_status[button_num] = BUTTON_RELEASE; // 다음 버튼 체크를 위해서 초기화
		return BUTTON_PRESS; // 완전히 1번 눌렀다 떼어진 상태로 인정
	}
	return BUTTON_RELEASE; // 버튼이 OPEN상태
}


///////////////////// hc595 setting
void send_1byte74hc595_led(uint8_t data)
{
   for (int i = 0; i <8; i++)
   {
	   if(data & (1 << i))
	   HAL_GPIO_WritePin(GPIOC, SER2_74HC595_Pin, 1);
	   else
	   HAL_GPIO_WritePin(GPIOC, SER2_74HC595_Pin, 0);

		 HAL_GPIO_WritePin(GPIOC, CLK2_74HC595_Pin, 1);
		 HAL_GPIO_WritePin(GPIOC, CLK2_74HC595_Pin, 0);
   }
}

void led_init(void)
{
   // idle
   HAL_GPIO_WritePin(GPIOC, CLK2_74HC595_Pin, 0);
   HAL_GPIO_WritePin(GPIOC, SER2_74HC595_Pin, 0);
   HAL_GPIO_WritePin(GPIOC, LATCH2_74HC595_Pin, 0);
   HAL_Delay(10);   // 안정화 시간
}
////////////////////////여기까지


void elevator_button_check(void) // 몇 번 버튼이 눌렸는지 check 후 Queue에 삽입 , os 1번
{
	static uint8_t led_data;
	static uint8_t led_data2;
	int button_state=0;
	init_button();
	if(get_button(GPIOC,GPIO_PIN_0, BTN0) == BUTTON_PRESS)
	{
		button_state = 0+1;
		led_data = 0x03;
		beep();
	}
	else if(get_button(GPIOC,GPIO_PIN_1, BTN1) == BUTTON_PRESS)
	{
		button_state = 1+1;
		led_data = 0x0C;
		beep();
	}
	else if(get_button(GPIOC,GPIO_PIN_2, BTN2) == BUTTON_PRESS)
	{
		button_state = 2+1;
		led_data = 0x30;
		beep();
	}
	else if(get_button(GPIOC,GPIO_PIN_3, BTN3) == BUTTON_PRESS)
	{
		button_state = 3+1;
		led_data = 0xC0;
		beep();
	}

	if(!queue_full() && button_state != 0) // 만약 큐가 다 차지 않았고 버튼이 눌렸다면
	{
		insert_queue(button_state);
		button_state = 0;
	}

	if(led_data2 != led_data) {

		 send_1byte74hc595_led(led_data);
		 GPIOC->ODR &= ~LATCH2_74HC595_Pin;   // latch핀을 pull-down
		 GPIOC->ODR |= LATCH2_74HC595_Pin;   // latch핀을 pull-up
		 led_data2 = led_data;

	}


}





