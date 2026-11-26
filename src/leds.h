/*
 * Copyright (c) 2022-2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MY_LEDS_H_
#define MY_LEDS_H_

#include "leds_config.h"

typedef enum LEDS_Leds_e {
#if LEDS_CONFIG_HAS_RED_LED
  LEDS_RED,
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  LEDS_GREEN,
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  LEDS_BLUE,
#endif
} LEDS_Leds_e;

/* turn LED on */
void LEDS_On(LEDS_Leds_e led);

/* turn LED off */
void LEDS_Off(LEDS_Leds_e led);

/* toggle LED */
void LEDS_Neg(LEDS_Leds_e led);

/* call it to initialize the driver */
void LEDS_Init(void);

/* use this after the driver is not needed any more */
void LEDS_Deinit(void);

#endif /* MY_LEDS_H_ */
