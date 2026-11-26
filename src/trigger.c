/*
 * Copyright (c) 2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "IncludeMcuLibConfig.h"
#include "McuGPIO.h"

#if McuLib_CONFIG_CPU_IS_LPC
   /* Pin10 on J12: PIO0_9 */
  #define TRIGGER_ENABLE_CLOCK()       //GPIO_EnablePortClock(GPIO, 0) /* ungate the clocks for GPIO0 */

  #define TRIGGER_GPIO         GPIO
  #define TRIGGER_PORT         0
  #define TRIGGER_PIN          9
  #define TRIGGER_IOCON        IOCON_INDEX_PIO0_9
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define TRIGGER_ENABLE_CLOCK()       CLOCK_EnableClock(kCLOCK_PortE) /* ungate the clocks for PORTE */

  #define TRIGGER_GPIO        GPIOE
  #define TRIGGER_PORT        PORTE
  #define TRIGGER_PIN         1U
#endif

static McuGPIO_Handle_t triggerPin = NULL;

void Trigger_Assert(void){
    McuGPIO_SetHigh(triggerPin);
}

void Trigger_Deassert(void) {
    McuGPIO_SetLow(triggerPin);
}

void Trigger_Deinit(void) {
    triggerPin = McuGPIO_DeinitGPIO(triggerPin);
}

void Trigger_Init(void) {
 McuGPIO_Config_t config;

  TRIGGER_ENABLE_CLOCK();
  McuGPIO_GetDefaultConfig(&config);
  config.isHighOnInit = false;
  config.isInput = false;
  config.hw.gpio = TRIGGER_GPIO;
  config.hw.port = TRIGGER_PORT;
  config.hw.pin = TRIGGER_PIN;
  #if McuLib_CONFIG_CPU_IS_LPC
  config.hw.iocon = TRIGGER_IOCON;
  #endif
  triggerPin = McuGPIO_InitGPIO(&config);
  if (triggerPin==NULL) {
    for(;;) {}
  }
}