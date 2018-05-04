#include "stm32f1xx_hal.h"
#include "DAC7821.h"
#include "time.h"
#include "gpio.h"
#include "tim.h"

uint16_t wave_cnt=0;
uint16_t amp_bottom=0;
uint16_t sanjiaobo_amp_step=0;

int wave_flag=1;
uint16_t juchibo_amp_step_1=0;
uint16_t juchibo_amp_step_2=0;

uint8_t wave_choose=0;

//GPIO已经设置好了
void DAC7821_init(void){
	DAC7821_RW_OFF;
	DAC7821_CS_OFF;
}

void DAC7821_vol(float vol){//直流电压
	uint16_t vol_data=0;
	vol_data = (uint16_t) (vol * 4095/150);
	DATAOUT_DAC7821(vol_data);
	DAC7821_RW_ON;
	DAC7821_CS_ON;
	HAL_Delay(1);
	DAC7821_CS_OFF;
	DAC7821_RW_OFF;
}

void data_send_DAC7821(uint16_t data){
	DATAOUT_DAC7821(data);
	DAC7821_RW_ON;
	DAC7821_CS_ON;//可以不用延时？
	DAC7821_CS_OFF;
	DAC7821_RW_OFF;
}


void sanjiaobo(uint16_t fre,uint8_t amp1,uint8_t amp2){
	uint16_t amp=amp2-amp1;
	amp_bottom=4095/150*amp1;
	wave_choose=0;
	wave_cnt=0;
	wave_flag=1;
	
	sanjiaobo_amp_step=4095/150*amp/200;
	 RCC->AHBENR|=1<<1;//TIM3时钟使能
	if(fre<=2){
		if(fre==1)
			TIM3->ARR=60000;
		if(fre==2)
			TIM3->ARR=30000;
		TIM3->PSC=2;//3分频，得到24M的计数时钟
	}else{
		fre=2500/fre*72;
		TIM3->ARR=(uint16_t)fre;
		TIM3->PSC=0;
	}
	TIM1->DIER=1<<0;//允许更新中断
	TIM3->CR1|=0x01;//使能定时器3
	HAL_TIM_Base_Start_IT(&htim3);//开启定时器3

}

void juchibo(uint16_t fre,uint8_t amp1,uint8_t amp2){
	uint16_t amp=amp2-amp1;
	amp_bottom=4095/150*amp1;
	wave_choose=1;//选择锯齿波
	wave_cnt=0;
	wave_flag=1;
	
	juchibo_amp_step_1=4095/150*amp/359;
	juchibo_amp_step_2=4095/150*amp/39;

	RCC->APB1ENR|=1<<1;//TIM3时钟使能
	if(fre<=2){
		if(fre==1)
			TIM3->ARR=60000;
		if(fre==2)
			TIM3->ARR=30000;
		TIM3->PSC=2;//3分频，得到24M的计数时钟
	}else{
		fre=2500*72/fre;
		TIM3->ARR=(uint16_t) fre;
		TIM3->PSC=0;
	}
	TIM3->DIER|=1<<0;//允许更新中断
	TIM3->CR1|=0X01;//使能定时器3
	HAL_TIM_Base_Start_IT(&htim3);//开启定时器3
}

void DAC7821_ShutDown(){
	DATAOUT_DAC7821(0x00);
	DAC7821_RW_ON;
	DAC7821_CS_ON;//可以不用延时？
	DAC7821_CS_OFF;
	DAC7821_RW_OFF;
}




