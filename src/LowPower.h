/*
 * Copyright (c) 2024-2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LOWPOWER_H_
#define LOWPOWER_H_

/* clock modes, enable only one: */
#define LP_CLOCK_MODE_PLL_120_MHz   (1)
#define LP_CLOCK_MODE_PEE_10_MHz    (0)

/* low power modes */
#define LP_WAIT_MODE  1
#define LP_STOP_MODE  2

#if 0
  #define LP_LOW_POWER_MODE   LP_RUN_MODE  /* normal run mode, no low power modes */
#elif 0
  #define LP_LOW_POWER_MODE   LP_WAIT_MODE /* wait mode with WFI, interrupt will wake us up */
#elif 1
  #define LP_LOW_POWER_MODE   LP_STOP_MODE /* stop mode, interrupt will wake us up */
#endif

#define LP_CONFIG_USE_LP_TIMER    		 (0) /* if using LPTMR0 as wake-up source, for WAIT or STOP mode */

void LP_EnterLowPowerMode(void);

void LP_Init(void);

#endif /* LOWPOWER_H_ */
