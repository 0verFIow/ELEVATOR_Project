
#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

#include "led.h"
#include "extern.h"



#define BTN0 0 // PC0
#define BTN1 1 // PC1
#define BTN2 2 // PC2
#define BTN3 3 // PC3
#define BTN4 4 // PC4, BLUE BUTTON

#define BUTTON_PRESS 0 // active low
#define BUTTON_RELEASE 1 // button을 뗀 상태

#define BUTTON_NUMBER 5
#define GPIOB_IDR 0x0040020810
#define GPIOB_ODR 0x0040020814
#define GPIOC_PUPDR 0x04002080C
#define GPIOC_IDR 0x040020810

int get_button(GPIO_TypeDef *GPIO,int button_pin, int button_num);
void button_led_toggle_test(void);
void button_check(void);

#endif
