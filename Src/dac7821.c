#include "stm32f1xx_hal.h"
#include "DAC7821.h"

uint16_t wave_cnt=0;
float amp_bottom=0;
float sanjiaobo_amp_step=0;

int wave_flag=1;
float juchibo_amp_step_1=0;
float juchibo_amp_step_2=0;

uint8_t wave_choose=0;

//GPIO已经设置好了
void DAC7821_init(void){
	DAC7821_RW_OFF;
	DAC7821_CS_OFF;
}

void DAC7821_vol(float vol){
	uint16_t vol_data=0;
	vol_data = (uint16_t) vol * 4095/10;
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







