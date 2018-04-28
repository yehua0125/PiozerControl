/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOE
#define DAC7821RW_Pin GPIO_PIN_13
#define DAC7821RW_GPIO_Port GPIOC
#define DAC7821DATA_Pin GPIO_PIN_0
#define DAC7821DATA_GPIO_Port GPIOC
#define DAC7821DATAC1_Pin GPIO_PIN_1
#define DAC7821DATAC1_GPIO_Port GPIOC
#define DAC7821DATAC2_Pin GPIO_PIN_2
#define DAC7821DATAC2_GPIO_Port GPIOC
#define DAC7821DATAC3_Pin GPIO_PIN_3
#define DAC7821DATAC3_GPIO_Port GPIOC
#define DAC7821DATAC4_Pin GPIO_PIN_4
#define DAC7821DATAC4_GPIO_Port GPIOC
#define DAC7821DATAC5_Pin GPIO_PIN_5
#define DAC7821DATAC5_GPIO_Port GPIOC
#define DAC7821DATAC6_Pin GPIO_PIN_6
#define DAC7821DATAC6_GPIO_Port GPIOC
#define DAC7821DATAC7_Pin GPIO_PIN_7
#define DAC7821DATAC7_GPIO_Port GPIOC
#define DAC7821DATAC8_Pin GPIO_PIN_8
#define DAC7821DATAC8_GPIO_Port GPIOC
#define DAC7821DATAC9_Pin GPIO_PIN_9
#define DAC7821DATAC9_GPIO_Port GPIOC
#define DAC7821DATAC10_Pin GPIO_PIN_10
#define DAC7821DATAC10_GPIO_Port GPIOC
#define DAC7821DATAC11_Pin GPIO_PIN_11
#define DAC7821DATAC11_GPIO_Port GPIOC
#define DAC7821CS_Pin GPIO_PIN_12
#define DAC7821CS_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_5
#define LED0_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
