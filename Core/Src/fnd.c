#include "fnd.h"
#include "extern.h"
#include "ds1302.h"

uint8_t fnd_font[] = {
   ~0xc0, // 0
   ~0xf9, // 1
   ~0xa4, // 2
   ~0xb0, // 3
   ~0x99, // 4
   ~0x92, // 5
   ~0x82, // 6
   ~0xd8, // 7
   ~0x80, // 8
   ~0x98, // 9
   ~0x7f  // .
};

void send_1byte74hc595_fnd(uint8_t data)
{
   for (int i = 0; i <8; i++)
   {
   if(data & (1 << i))
   HAL_GPIO_WritePin(GPIOB, SER1_74HC595_Pin, 1);
   else
   HAL_GPIO_WritePin(GPIOB, SER1_74HC595_Pin, 0);

     HAL_GPIO_WritePin(GPIOB, CLK1_74HC595_Pin, 1);
     HAL_GPIO_WritePin(GPIOB, CLK1_74HC595_Pin, 0);
   }
}

void fnd_init(void)
{
   // idle
   HAL_GPIO_WritePin(GPIOB, CLK1_74HC595_Pin, 0);
   HAL_GPIO_WritePin(GPIOB, SER1_74HC595_Pin, 0);
   HAL_GPIO_WritePin(GPIOB, LATCH1_74HC595_Pin, 0);
   HAL_Delay(10);   // 안정화 시간
}


uint8_t fnd_data[4]={0,0,0,0};

void fnd_time()
{
      uint8_t temp;
      read_time_ds1302();
      read_date_ds1302();

      static int i = 0;

      fnd_data[0] = ~(1 << (i+4));      // 자릿수 선택

   //ds1302.minutes
   //ds1302.hours

   switch(i)
      {
      case 0:
        fnd_data[1] = fnd_font[ds1302.minutes % 10];
        break;
      case 1:
        fnd_data[1] = fnd_font[ds1302.minutes / 10];
        break;
      case 2 :
        fnd_data[1] = fnd_font[ds1302.hours % 10];
        break;
      case 3:
        fnd_data[1] = fnd_font[ds1302.hours / 10];
        break;
      }

      for(int j = 0; j<2; j++)
      {
         temp = fnd_data[j]; // 보낼 데이터 (1바이트)
         send_1byte74hc595_fnd(temp);
      }
   i++;
   i %=4;
   GPIOB->ODR &= ~LATCH1_74HC595_Pin;   // latch핀을 pull-down
   GPIOB->ODR |= LATCH1_74HC595_Pin;   // latch핀을 pull-up
}
