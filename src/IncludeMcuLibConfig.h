/*
 * Copyright (c) 2016-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       (McuLib_CONFIG_CPU_VARIANT_NXP_LPC845) /* for LPC need to specify the actual device */
#elif 1 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)
#define configTOTAL_HEAP_SIZE                (24*1024)
#define configUSE_HEAP_SECTION_NAME          (1)
#define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS"
/* ------------------- McuShellUart ---------------------------*/
#define McuShellUart_CONFIG_IS_ENABLED        (1)
#define McuShellUart_CONFIG_UART              McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4

#define configUSE_TICKLESS_IDLE              (0)
#define configTICK_RATE_HZ                   (1000)

#define configUSE_IDLE_HOOK                   (1)
#define configUSE_TICK_HOOK                   (1)
#define configGENERATE_RUN_TIME_STATS         (1)

#define configUSE_TRACE_FACILITY              (1)
#define configGENERATE_RUN_TIME_STATS         (1)
#define configCHECK_FOR_STACK_OVERFLOW        (2)
//#define configASSERT(x)                   /* empty */
#define configUSE_TIMERS                      (1)
#define INCLUDE_xTimerPendFunctionCall        (1)

#define configSYSTICK_USE_LOW_POWER_TIMER     (0)
#define config_USE_STOP_MODE                  (0  && configSYSTICK_USE_LOW_POWER_TIMER)
/* ---------------------------------------------------------------------------------------*/
/* Unity */
#if ENABLE_UNIT_TESTS
    #if !__ASSEMBLER__ /* set if file is included by GNU as (assembler). Do not include normal C header files if running the assembler for example to assemble the pico startup code */
    #include "McuUnity.h"
    #define UNITY_OUTPUT_CHAR(a)                        McuUnity_putc(a)
    #define UNITY_OUTPUT_FLUSH()                        McuUnity_flush()
    #define UNITY_OUTPUT_START()                        McuUnity_start()
    #define UNITY_OUTPUT_COMPLETE()                     McuUnity_complete()
    #define UNITY_OUTPUT_COLOR                          /* use colored output */
    #endif
#endif
/* ---------------------------------------------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP       (32)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN     (8)
#define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS   (3)
#define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS (3)
/* ---------------------------------------------------------------------------------------*/
/* SystemView */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS  (1)
#define McuSystemView_CONFIG_RTT_BUFFER_SIZE  (256)
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS             (0)

#endif /* INCLUDEMCULIBCONFIG_H_ */
