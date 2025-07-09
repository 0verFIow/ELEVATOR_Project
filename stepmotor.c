#include "stepmotor.h"
#include "button.h"
#include "extern.h"

/*
 * RPM(Revolutions Per Minutes : 분당 회전수)
 * 1분 -> 60초 = 60,000,000us
 * 1초 : 1000ms --> 1ms : 1000us * 1000ms = 1,000,000us
 * 1바퀴 회전: 4096 step 필요
 * 4096 / 8 ==> 512sequence : 360도 회전
 * 1 sequence (8step) : 0.70312도
 * 0.70312 x 512 sequence : 360도 회전
 *  ---- RPM 조절 ----
 *  예) 1분에 13회전이 최대 속도
 *  13회전 : 60,000,000us(1분) / 4096 / 13 ==> step과 step간의 간격 time : 1126us
 *  1126us x 4096(1회전 하는데 필요 스텝) = 4,615,384us
 *  								 = 4615ms(4.6초)
 * 60초 / 4.6초 (1회전 하는데 소요 시간) : 13회전
 */
uint8_t stepmotor_state = IDLE;
uint8_t current_state = 5;
uint8_t go = 0; // 엘레베이터가 작동 중인지 확인 변수
uint8_t arrive = 0;
uint8_t flag = 0; // 도착해서 엘레베이터가 멈추는걸 check하는 flag

void stepmotor_main(void);
void set_rpm(int rpm);
void stepmotor_drive(int step);

void set_rpm(int rpm) // rpm : 1 ~13
{
	delay_us(60000000/4096/rpm);
	// 최대 speed기준(13) : delay_us(1126);
}
// stepmotor
void stepmotor_main(void)
{
#if 1 // OS

	if(!queue_empty() && !go) // 큐에 값이 들어있고, 엘레베이터가 작동 중이 아니라면
	{
		arrive = check_queue();
		go=1;
		if(current_state < arrive) // 현재 층이 도착해야하는 층보다 낮을 경우
		{
			display_lcd(FW);
			stepmotor_state = FW;
		}
		else if (current_state > arrive) // 현재 층이 도착해야하는 층보다 높을 경우
		{
			display_lcd(BW);
			stepmotor_state = BW;
		}
		else // 현재 층이 도착해야하는 층과 같을 경우
		{
			display_lcd(IDLE);
			stepmotor_state = IDLE;
		}
//printf("1current = %d , arrive = %d , state = %d, go = %d\n",current_state,arrive,stepmotor_state,go);
	}

	if(flag)
	{
		stepmotor_state = IDLE;
		display_lcd(IDLE);
		de_queue();
		current_state = arrive;
		arrive=0;
		go=0;
		flag=0;
	}

	switch(stepmotor_state)
	{
	case IDLE:
		break;
	case FW:
		stepmotor_drive(FW);
		set_rpm(13); // 1126us wait
		break;
	case BW:
		stepmotor_drive(BW);
		set_rpm(13); // 1126us wait
		break;
	}
#endif

#if 0 // OS

	if(!queue_empty() && !go) // 큐에 값이 들어있고, 엘레베이터가 작동 중이 아니라면
	{
		arrive = check_queue();
		go=1;
		if(current_state < arrive) // 현재 층이 도착해야하는 층보다 낮을 경우
		{
			stepmotor_state = FW;
		}
		else if (current_state > arrive) // 현재 층이 도착해야하는 층보다 높을 경우
		{
			stepmotor_state = BW;
		}
		else // 현재 층이 도착해야하는 층과 같을 경우
		{
			stepmotor_state = IDLE;
		}
	}

	switch(stepmotor_state)
	{
	case IDLE:
		continue;
		break;
	case FW:
		stepmotor_drive(FW);
		set_rpm(13); // 1126us wait
		break;
	case BW:
		stepmotor_drive(BW);
		set_rpm(13); // 1126us wait
		break;
	}
#endif
}

void stepmotor_drive(int direction)
{
	static int step;

	switch(step)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOC, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOC, IN4_Pin, 1);
		break;
	}
	if(direction == FW)
	{
		step++;
		step %= 8; // 다음 진행할 step for(int=0;i<8;i++)
	}
	else if(direction == BW)
	{
		if(step <= 0)
		{
			step = 7;
		}
		else
		{
			step--;
		}
	}
	else
	{
		step=0;
	}
}




