/*
 * Copyright (c) 2024-2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "LowPower.h"
#include "leds.h"
#include "McuWait.h"
#include "McuLED.h"
#include "clock_config.h"
#include "fsl_smc.h"

#if LP_LOW_POWER_MODE==LP_WAIT_MODE
void LP_EnterWaitMode(void) {
  __asm volatile("dsb");
  __asm volatile("wfi");
  __asm volatile("isb");
}
#endif

#if LP_LOW_POWER_MODE==LP_STOP_MODE
void LP_EnterStopMode(void) {
  status_t status;

  SMC_PreEnterStopModes();
  status = SMC_SetPowerModeStop(SMC, kSMC_PartialStop);
  SMC_PostExitStopModes();
  if (status!=kStatus_Success) {
    for(;;) {}
  }
}
#endif

void LP_EnterLowPowerMode(void) {
#if LP_LOW_POWER_MODE==LP_RUN_MODE
	/* nothing needed */
#elif LP_LOW_POWER_MODE==LP_WAIT_MODE
  LP_EnterWaitMode();
#elif LP_LOW_POWER_MODE==LP_STOP_MODE
  LP_EnterStopMode();
#endif
}

void LP_Init(void) {
  /* safety belt */
  for(int i= 0; i<5; i++) {
    #if LEDS_CONFIG_HAS_BLUE_LED
      LEDS_Neg(LEDS_BLUE);
    #endif
    McuWait_Waitms(1000);
  }
  #if LEDS_CONFIG_HAS_BLUE_LED
    LEDS_Off(LEDS_BLUE);
  #endif
}
