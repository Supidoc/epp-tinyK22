/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

#if McuLib_CONFIG_CPU_IS_LPC
   /* Green: PIO0_13
    * Red:   PIO0_12 */
  #define LEDS_ENABLE_CLOCK()       GPIO_PortInit(GPIO, 0) /* ungate the clocks for GPIO0: used for LEDs */

  #define LEDS_LED_RED_GPIO         GPIO
  #define LEDS_LED_RED_PORT         0
  #define LEDS_LED_RED_PIN          12
  #define LEDS_LED_RED_LOW_ACTIVE   false
  #define LEDS_LED_RED_IOCON        IOCON_INDEX_PIO0_12

  #define LEDS_LED_GREEN_GPIO       GPIO
  #define LEDS_LED_GREEN_PORT       0
  #define LEDS_LED_GREEN_PIN        13
  #define LEDS_LED_GREEN_LOW_ACTIVE false
  #define LEDS_LED_GREEN_IOCON      IOCON_INDEX_PIO0_13

  #define LEDS_CONFIG_HAS_RED_LED   (1)
  #define LEDS_CONFIG_HAS_GREEN_LED (1)
  #define LEDS_CONFIG_HAS_BLUE_LED  (0)

#elif McuLib_CONFIG_CPU_IS_KINETIS
  #define LEDS_ENABLE_CLOCK()       CLOCK_EnableClock(kCLOCK_PortC) /* ungate the clocks for PORTC: used for LEDs */

  #define LEDS_LED_BLUE_GPIO        GPIOC
  #define LEDS_LED_BLUE_PORT        PORTC
  #define LEDS_LED_BLUE_PIN         2U
  #define LEDS_LED_BLUE_LOW_ACTIVE  true

  #define LEDS_CONFIG_HAS_RED_LED   (0)
  #define LEDS_CONFIG_HAS_GREEN_LED (0)
  #define LEDS_CONFIG_HAS_BLUE_LED  (1)
#endif

#endif /* LEDS_CONFIG_H_ */
