/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "dac.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "dac7821.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
uint16_t OldDyOneSet;			//上一次三角波电压
uint16_t NewDyOneSet;			//新的三角波电压
uint16_t OldDyTwoSet;			//上一次锯齿波电压
uint16_t NewDyTwoSet;			//新的锯齿波电压
uint16_t OldDyZeroSet;			//上一次直流电压电压
uint16_t NewDyZeroSet;			//新的直流电压
uint16_t NewVoltSet;

uint16_t OldFreOneSet;
uint16_t NewFreOneSet;
uint16_t OldFreTwoSet;
uint16_t NewFreTwoSet;
uint16_t NewFreSet;



int volt_Flag=0;					//电压模式标志
int volt_Change=0;				//电压改变标志

/* USER CODE BEGIN PV */

/* Private variables ---------------------------------------------------------*/
/* Buffer used for reception */
uint8_t aTxStartMessage[]="\r\n the project start \r\n";
uint8_t aDyZeroMessage[]="the dy0 ok\r\n";
uint8_t aDyOneMessage[]="the dy1 ok\r\n";
uint8_t aDyTwoMessage[]="the dy2 ok\r\n";

uint8_t aDfOneMessage[]="the df1 ok\r\n";
uint8_t aDfTwoMessage[]="the df2 ok\r\n";
uint8_t aDyBuffer[20];		//电压接收buffer
char Message[]="";
int out_flag=1;

extern uint8_t wave_choose;
extern uint16_t wave_cnt;
extern int wave_flag;
extern uint16_t amp_bottom;
extern uint16_t sanjiaobo_amp_step;
extern uint16_t juchibo_amp_step_1;
extern uint16_t juchibo_amp_step_2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
char *myitoa(uint16_t value, char *string, int radix);  
void voltSet(int flag,uint16_t voltSet,uint16_t freSet);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint16_t i=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	/* 外设初始化 */
	DAC7821_init();
	/*全局设置(TIM,UART)*/
	//HAL_TIM_Base_Start_IT(&htim3);//开启定时器3
	//HAL_TIM_Base_Stop_IT(&htim3);//关闭定时器3
	HAL_UART_Transmit_IT(&huart1,(uint8_t *)aTxStartMessage,sizeof(aTxStartMessage));
	HAL_UART_Receive_IT(&huart1,(uint8_t *)aDyBuffer,6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	uint32_t i=1000000;
//		while(i--);
//		Led1_Toggle();
	if(volt_Change){
		voltSet(volt_Flag,NewVoltSet,NewFreSet);
		volt_Change=0;
		//Led0_Toggle();
	}
		
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
/**
	* @brief int转String
  * @param value string radix
  * @retval String
	* @effect 将Int变量转换为String 
	*/
char *myitoa(uint16_t value, char *string, int radix)  
{  
    int i, d;  
    int flag = 0;  
    char *ptr = string;  
		
		if(radix!=10){
			*ptr=0;
			return string;
		}
		if(!value){
			*ptr++=0x30;
			*ptr=0;
			return string;
		}
		for(i=10000;i>0;i /=10){
			d=value/i;
			if(d||flag){
				*ptr++=(char)(d+0x30);
				value-=(d*i);
				flag=1;
			}
		}
		*ptr=0;
		
    return string;  
  
} /* NCL_Itoa */  

/**
	* @brief 定时器回调函数
  * @param huart: htim handle
  * @retval None
	* @effect 处理定时器3溢出函数 波形产生
	*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==htim3.Instance){
		//tim3定时器溢出
		
			if(wave_choose==0){
				data_send_DAC7821(amp_bottom+sanjiaobo_amp_step*wave_cnt);
				wave_cnt=wave_cnt+wave_flag;
				
				if(wave_cnt>=200)
					wave_flag =-1;
				if(wave_cnt==0)
					wave_flag=1;
				Led1_Toggle();
			}
			if(wave_choose==1){
				if(wave_flag==1){
					data_send_DAC7821(amp_bottom+juchibo_amp_step_1*wave_cnt);
				}
				else {
					data_send_DAC7821(amp_bottom+juchibo_amp_step_2*wave_cnt);
				}
					wave_cnt=wave_cnt+wave_flag;
				if(wave_cnt==359){
					wave_flag=-1;
					wave_cnt=39;
				}
				if(wave_cnt==0)
					wave_flag=1;
			}
		}
}

/**
	* @brief Rx Transfer completed callbacks  中断回调函数
  * @param huart: uart handle
  * @retval None
	* @effect 接收上位机传送给MCU的电压设置参数
	*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	UNUSED(huart);
	out_flag=1;
	HAL_TIM_Base_Stop_IT(&htim3);//关闭定时器3
	volt_Change=1;
	if((aDyBuffer[0] == 'd')&&(aDyBuffer[1] =='y')&&(aDyBuffer[2] == '0')){
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *)aDyZeroMessage,sizeof(aDyZeroMessage));
	printf(aDyZeroMessage);
	//dy0接收成功 
	NewDyZeroSet=(aDyBuffer[3]-48)*100 + (aDyBuffer[4]-48)*10 + (aDyBuffer[5]-48);
	if(NewDyZeroSet>150) NewDyZeroSet=150;
	myitoa(NewDyZeroSet,Message,10);
	printf("new dy0=: \r\n");
	printf(Message);
	NewVoltSet=NewDyZeroSet;
	volt_Flag=1;
	}
	
	else if((aDyBuffer[0] == 'd')&&(aDyBuffer[1] =='y')&&(aDyBuffer[2] == '1')){
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *)aDyOneMessage,sizeof(aDyOneMessage));
	printf(aDyOneMessage);
		//dy1接收成功 
	//字符换算成int
	NewDyOneSet=(aDyBuffer[3]-48)*100 + (aDyBuffer[4]-48)*10 + (aDyBuffer[5]-48);
	if(NewDyOneSet>150) NewDyOneSet=150;
	myitoa(NewDyOneSet,Message,10);
	printf("new dy1=: \r\n");
	printf(Message);
	NewVoltSet=NewDyOneSet;
	volt_Flag=2;
	}
	else if((aDyBuffer[0] == 'd')&&(aDyBuffer[1] =='f')&&(aDyBuffer[2] == '1')){
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *)aDyZeroMessage,sizeof(aDyZeroMessage));
	printf(aDfOneMessage);
	//dy0接收成功 
	NewFreOneSet=(aDyBuffer[3]-48)*100 + (aDyBuffer[4]-48)*10 + (aDyBuffer[5]-48);
	if(NewFreOneSet>500) NewFreOneSet=500;
	myitoa(NewFreOneSet,Message,10);
	printf("new df1=: \r\n");
	printf(Message);
	NewFreSet=NewFreOneSet;
	volt_Flag=2;
	}
	
	else if((aDyBuffer[0] == 'd')&&(aDyBuffer[1] =='y')&&(aDyBuffer[2] == '2')){
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *)aDyTwoMessage,sizeof(aDyTwoMessage));
	printf(aDyTwoMessage);
	//dy2接收成功 
	//字符换算成int
	NewDyTwoSet=(aDyBuffer[3]-48)*100 + (aDyBuffer[4]-48)*10 + (aDyBuffer[5]-48);
	if(NewDyTwoSet>150) NewDyTwoSet=150;
	myitoa(NewDyTwoSet,Message,10);
	printf("new dy2=: \r\n");
	printf(Message);
	NewVoltSet=NewDyTwoSet;
	volt_Flag=3;
	}
	
	else if((aDyBuffer[0] == 'd')&&(aDyBuffer[1] =='f')&&(aDyBuffer[2] == '2')){
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *)aDyZeroMessage,sizeof(aDyZeroMessage));
	printf(aDfTwoMessage);
	//dy0接收成功 
	NewFreTwoSet=(aDyBuffer[3]-48)*100 + (aDyBuffer[4]-48)*10 + (aDyBuffer[5]-48);
	if(NewFreTwoSet>500) NewFreTwoSet=500;
	myitoa(NewFreTwoSet,Message,10);
	printf("new df2=: \r\n");
	printf(Message);
	NewFreSet=NewFreTwoSet;
	volt_Flag=3;
	}
	else if((aDyBuffer[0] == 'd')&&(aDyBuffer[1] =='y')&&(aDyBuffer[2] == 'd')&&(aDyBuffer[3] == 'w')){
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *)aDyZeroMessage,sizeof(aDyZeroMessage));
	volt_Flag=5;
	}
	else {
		printf("输入错误");
		volt_Change=0;
	}
	
	printf("\r\n");
	HAL_UART_Receive_IT(&huart1,(uint8_t *)aDyBuffer,6);
}

/**
	* @brief 电压设置函数
  * @param flag,voltset,freset
  * @retval None
	* @effect  电压设置函数 输出DAC的选择
	*/
void voltSet(int flag,uint16_t voltSet,uint16_t freSet){
	if(volt_Flag==1){
		if(OldDyZeroSet!=voltSet){
			Led0_Toggle();
			DAC7821_vol(voltSet);
			OldDyZeroSet=voltSet;
		}
	}
	else if(volt_Flag==2){
		if((voltSet!=0)&&(freSet!=0)&&(OldDyOneSet!=voltSet||OldFreOneSet!=freSet)){
			Led0_Toggle();
			sanjiaobo(freSet,0,voltSet);
			OldDyOneSet=voltSet;
			OldFreOneSet=freSet;
		}
	}
	else if(volt_Flag==3){
		if((voltSet!=0)&&(freSet!=0)&&(OldDyTwoSet!=voltSet||OldFreTwoSet!=freSet)){
			Led0_Toggle();
			juchibo(freSet,0,voltSet);
			OldDyTwoSet=voltSet;
			OldFreTwoSet=freSet;
		}
	}else	if(volt_Flag==5){
		DAC7821_ShutDown();
	}
		
}

		
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
