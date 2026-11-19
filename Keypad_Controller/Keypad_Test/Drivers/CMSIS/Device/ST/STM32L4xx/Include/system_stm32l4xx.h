/**
  ******************************************************************************
  * @file    system_stm32l4xx.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M4 Device System Source File for STM32L4xx devices.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l4xx_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32L4XX_H
#define __SYSTEM_STM32L4XX_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32L4xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup STM32L4xx_System_Exported_Variables
  * @{
  */
  /* Project modification: call SystemCoreClockUpdate() after clock changes. */
extern uint32_t SystemCoreClock;            /*!< System Clock Frequency (Core Clock) */

extern const uint8_t  AHBPrescTable[16];    /*!< AHB prescalers table values */
extern const uint8_t  APBPrescTable[8];     /*!< APB prescalers table values */
extern const uint32_t MSIRangeTable[12];    /*!< MSI ranges table values     */

/**
  * @}
  */

/** @addtogroup STM32L4xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32L4xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32L4xx_System_Exported_Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32L4XX_H */

/**
  * @}
  */

/**
  * @}
  */

