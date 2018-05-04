
#ifndef __DAC7821_H
#define __DAC7821_H
#include "stm32f1xx_hal.h"
#define DAC7821_RW_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET); 
#define DAC7821_RW_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET); 
#define DAC7821_CS_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET); 
#define DAC7821_CS_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET); 
#define DATAOUT_DAC7821(x) GPIOC->ODR = x | (GPIOC->ODR&0XF000);

void DAC7821_init(void);
void DAC7821_vol(float vol);
void data_send_DAC7821(uint16_t data);
void sanjiaobo(uint16_t fre,uint8_t amp1,uint8_t amp2);
void juchibo(uint16_t fre,uint8_t amp1,uint8_t amp2);
void DAC7821_ShutDown();
#endif