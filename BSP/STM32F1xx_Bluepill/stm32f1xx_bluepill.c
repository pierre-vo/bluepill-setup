/**
  ******************************************************************************
  * @file    stm32f1xx_nucleo.c
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_bluepill.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup STM32F1XX_BLUEPILL STM32F103xx Bluepill
  * @{
  */ 


/** @defgroup STM32F1XX_BLUEPILL_Private_Defines STM32F1XX BLUEPILL Private Defines
  * @{
  */ 
  
/**
* @brief STM32F103RB BLUEPILL BSP Driver version
*/
#define __STM32F1XX_BLUEPILL_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32F1XX_BLUEPILL_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32F1XX_BLUEPILL_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32F1XX_BLUEPILL_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F1XX_BLUEPILL_BSP_VERSION       ((__STM32F1XX_BLUEPILL_BSP_VERSION_MAIN << 24)\
                                             |(__STM32F1XX_BLUEPILL_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32F1XX_BLUEPILL_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32F1XX_BLUEPILL_BSP_VERSION_RC))

   
/**
  * @}
  */ 


/** @defgroup STM32F1XX_BLUEPILL_Private_Variables STM32F1XX BLUEPILL Private Variables
  * @{
  */ 
GPIO_TypeDef* LED_PORT[LEDn] = {LED2_GPIO_PORT};

const uint16_t LED_PIN[LEDn] = {LED2_PIN};

GPIO_TypeDef* BUTTON_PORT[BUTTONn]  = {USER_BUTTON_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BUTTONn]  = {USER_BUTTON_PIN}; 
const uint8_t  BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn };

/**
 * @brief BUS variables
 */

#ifdef HAL_SPI_MODULE_ENABLED
uint32_t SpixTimeout = NUCLEO_SPIx_TIMEOUT_MAX;        /*<! Value of Timeout when SPI communication fails */
static SPI_HandleTypeDef hnucleo_Spi;
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
static ADC_HandleTypeDef hnucleo_Adc;
/* ADC channel configuration structure declaration */
static ADC_ChannelConfTypeDef sConfig;
#endif /* HAL_ADC_MODULE_ENABLED */

/**
  * @}
  */ 

/** @defgroup STM32F1XX_BLUEPILL_Private_Functions STM32F1XX BLUEPILL Private Functions
  * @{
  */ 


/**
  * @}
  */ 

/** @defgroup STM32F1XX_BLUEPILL_Exported_Functions STM32F1XX BLUEPILL Exported Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM32F1XX BLUEPILL BSP Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32F1XX_BLUEPILL_BSP_VERSION;
}

/** @defgroup STM32F1XX_BLUEPILL_LED_Functions STM32F1XX BLUEPILL LED Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Led to be configured. 
  *          This parameter can be one of the following values:
  *     @arg LED2
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpioinitstruct;
  
  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin    = LED_PIN[Led];
  gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(LED_PORT[Led], &gpioinitstruct);

  /* Reset PIN to switch off the LED */
  HAL_GPIO_WritePin(LED_PORT[Led],LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be de-init. 
  *   This parameter can be one of the following values:
  *     @arg  LED2
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx 
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Turn off LED */
  HAL_GPIO_WritePin(LED_PORT[Led],LED_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = LED_PIN[Led];
  HAL_GPIO_DeInit(LED_PORT[Led], gpio_init_structure.Pin);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED2
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET); 
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED2
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET); 
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *            @arg  LED2
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);
}

/**
  * @}
  */ 

/** @defgroup STM32F1XX_BLUEPILL_BUTTON_Functions STM32F1XX BLUEPILL BUTTON Functions
  * @{
  */ 

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_USER
  * @param  ButtonMode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability  
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef gpioinitstruct;

  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);

  gpioinitstruct.Pin = BUTTON_PIN[Button];
  gpioinitstruct.Pull = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

  if (ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;
  
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);
  }
 
  if (ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    gpioinitstruct.Mode   = GPIO_MODE_IT_FALLING; 
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Push Button DeInit.
  * @param  Button: Button to be configured
  *   This parameter should be: BUTTON_USER  
  * @note PB DeInit does not disable the GPIO clock
  */
void BSP_PB_DeInit(Button_TypeDef Button)
{
  GPIO_InitTypeDef gpio_init_structure;

  gpio_init_structure.Pin = BUTTON_PIN[Button];
  HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_USER
  * @retval Button state.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
  {
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
  }
/**
  * @}
  */ 

/**
  * @}
  */

/** @addtogroup STM32F1XX_BLUEPILL_Private_Functions
  * @{
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
    
/**
  * @}
  */ 
    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
