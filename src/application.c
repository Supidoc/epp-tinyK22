/*
 * Copyright (c) 2023-2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "leds.h"
#include "SelectionSort.h"
#include "trigger.h"

static void blink(bool isStart) {
  /* measurement is during HIGH trigger signal */
  if (isStart) {
    Trigger_Assert(); /* put high */
    McuWait_WaitOSms(1);
  }
  #if LEDS_CONFIG_HAS_GREEN_LED
    LEDS_On(LEDS_GREEN);
  #elif LEDS_CONFIG_HAS_BLUE_LED
    LEDS_On(LEDS_BLUE);
  #endif
  McuWait_WaitOSms(1);
  #if LEDS_CONFIG_HAS_GREEN_LED
    LEDS_Off(LEDS_GREEN);
  #elif LEDS_CONFIG_HAS_BLUE_LED
    LEDS_Off(LEDS_BLUE);
  #endif
  if (!isStart) {
    Trigger_Deassert(); /* put low */
  }
}

static void startMarker(void) {
  blink(true);
}

static void stopMarker(void) {
  blink(false);
}

static void workerJob(void) {
  startMarker();
  int arr[] = {0, 23, 14, 12, 9, 100, 22, 3, 5, 77, 20, 55, 100, 20, 70};
  for(int i=0; i<500; i++) {
    selectionSort(arr, sizeof(arr)/sizeof(arr[0]));
  }
  McuWait_WaitOSms(500);
  stopMarker();
}

#if McuLib_CONFIG_SDK_USE_FREERTOS
  static void blinky(void *pv) {
    for(;;) {
      workerJob();
      McuWait_WaitOSms(3000); /* to make the worker job a bit more clearly visible in the recording */
    }
  }
#else /* bare metal */
  static void bareMetal(void) {
    for(;;) {
      workerJob();
      McuWait_WaitOSms(3000); /* to make the worker job a bit more clearly visible in the recording */
    }
  }
#endif /* McuLib_CONFIG_SDK_USE_FREERTOS */

void APP_Run(void) {
  PL_Init();
#if McuLib_CONFIG_SDK_USE_FREERTOS
  if (xTaskCreate(blinky, "blinky", 300/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {
    for(;;) {}
  }
  vTaskStartScheduler();
#else
  bareMetal();
#endif
  for(;;) {} /* should not get here */
}
