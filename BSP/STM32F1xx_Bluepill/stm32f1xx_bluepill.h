/**
  ******************************************************************************
  * @file    stm32f1xx_bluepill.h
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1XX_BLUEPILL_H
#define __STM32F1XX_BLUEPILL_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32F1XX_BLUEPILL
  * @{
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdint.h>
   
   
/** @defgroup STM32F1XX_BLUEPILL_Exported_Types STM32F1XX BLUEPILL Exported Types
  * @{
  */
typedef enum 
{
  LED2 = 0,
  LED_BLUE = LED2
} Led_TypeDef;

typedef enum 
{  
  BUTTON_USER = 0,
  /* Alias */
  BUTTON_KEY  = BUTTON_USER
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef; 

/**
  * @}
  */ 

/** @defgroup STM32F1XX_BLUEPILL_Exported_Constants STM32F1XX BLUEPILL Exported Constants
  * @{
  */ 

/** 
  * @brief  Define for STM32F1xx_BLUEPILL board  
  */ 
#if !defined (USE_STM32F1xx_BLUEPILL)
 #define USE_STM32F1xx_BLUEPILL
#endif
  
/** @defgroup STM32F1XX_BLUEPILL_LED STM32F1XX BLUEPILL LED
  * @{
  */
#define LEDn                             1

#define LED2_PIN                         GPIO_PIN_2
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()  

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)   do { if((__INDEX__) == 0) LED2_GPIO_CLK_ENABLE();} while(0)
#define LEDx_GPIO_CLK_DISABLE(__INDEX__)  (((__INDEX__) == 0) ? LED2_GPIO_CLK_DISABLE() : 0)

/**
  * @}
  */ 

/** @defgroup STM32F1XX_BLUEPILL_BUTTON STM32F1XX BLUEPILL BUTTON
  * @{
  */  
#define BUTTONn                          1  

/**
  * @brief User push-button
 */
#define USER_BUTTON_PIN                  GPIO_PIN_0
#define USER_BUTTON_GPIO_PORT            GPIOA
#define USER_BUTTON_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define USER_BUTTON_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOA_CLK_DISABLE()
#define USER_BUTTON_EXTI_IRQn            EXTI15_10_IRQn
/* Aliases */
#define KEY_BUTTON_PIN                   USER_BUTTON_PIN
#define KEY_BUTTON_GPIO_PORT             USER_BUTTON_GPIO_PORT
#define KEY_BUTTON_GPIO_CLK_ENABLE()     USER_BUTTON_GPIO_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()    USER_BUTTON_GPIO_CLK_DISABLE()
#define KEY_BUTTON_EXTI_IRQn             USER_BUTTON_EXTI_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == 0) USER_BUTTON_GPIO_CLK_ENABLE();} while(0)
#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? USER_BUTTON_GPIO_CLK_DISABLE() : 0)
/**
  * @}
  */
    
/** @addtogroup STM32F1XX_BLUEPILL_BUS STM32F1XX BLUEPILL BUS
  * @{
  */
/*###################### SPI1 ###################################*/
// #define BLUEPILL_SPIx                                 SPI1
// #define BLUEPILL_SPIx_CLK_ENABLE()                    __HAL_RCC_SPI1_CLK_ENABLE()

// #define BLUEPILL_SPIx_SCK_GPIO_PORT                   GPIOA
// #define BLUEPILL_SPIx_SCK_PIN                         GPIO_PIN_5
// #define BLUEPILL_SPIx_SCK_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
// #define BLUEPILL_SPIx_SCK_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

// #define BLUEPILL_SPIx_MISO_MOSI_GPIO_PORT             GPIOA
// #define BLUEPILL_SPIx_MISO_MOSI_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
// #define BLUEPILL_SPIx_MISO_MOSI_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
// #define BLUEPILL_SPIx_MISO_PIN                        GPIO_PIN_6
// #define BLUEPILL_SPIx_MOSI_PIN                        GPIO_PIN_7
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define BLUEPILL_SPIx_TIMEOUT_MAX                   1000

    
/**
  * @}
  */
    

/**
  * @}
  */
    
/** @addtogroup STM32F1XX_BLUEPILL_Exported_Functions
  * @{
  */
uint32_t        BSP_GetVersion(void);
/** @addtogroup STM32F1XX_BLUEPILL_LED_Functions STM32F1XX BLUEPILL LED Functions
  * @{
  */ 

void            BSP_LED_Init(Led_TypeDef Led);
void            BSP_LED_DeInit(Led_TypeDef Led);
void            BSP_LED_On(Led_TypeDef Led);
void            BSP_LED_Off(Led_TypeDef Led);
void            BSP_LED_Toggle(Led_TypeDef Led);

/**
  * @}
  */

/** @addtogroup STM32F1XX_BLUEPILL_BUTTON_Functions STM32F1XX BLUEPILL BUTTON Functions
  * @{
  */

void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void             BSP_PB_DeInit(Button_TypeDef Button);
uint32_t         BSP_PB_GetState(Button_TypeDef Button);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1XX_BLUEPILL_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
