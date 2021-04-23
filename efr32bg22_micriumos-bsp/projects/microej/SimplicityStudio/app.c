/*
 * C
 *
 *  Copyright 2021 MicroEJ Corp. All rights reserved.
 *  This library is provided in source code for use, modification and test, subject to license terms.
 *  Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 *
 */

#include <stdio.h>
#include "em_device.h"
#include "os.h"
#include "rtos_prio.h"
#include "microej_main.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define JAVA_TASK_PRIORITY       (11)
#define MICROJVM_STACK_SIZE      (1024)
#define JAVA_TASK_STACK_SIZE     (MICROJVM_STACK_SIZE / sizeof(CPU_STK))

// Default Stacks, Pool Size, Stack Limit and Tasks.
#define  OS_INIT_CFG_DFLT                   { \
    .ISR =                                    \
    {                                         \
      .StkBasePtr = DEF_NULL,                 \
      .StkSize = 256u                         \
    },                                        \
    .MsgPoolSize = 100u,                      \
    .TaskStkLimit = 10u,                      \
    .StatTaskCfg =                            \
    {                                         \
      .StkBasePtr = DEF_NULL,                 \
      .StkSize = 256u,                        \
      .Prio = KERNEL_STAT_TASK_PRIO_DFLT,     \
      .RateHz = 10u                           \
    },                                        \
    .TmrTaskCfg =                             \
    {                                         \
      .StkBasePtr = DEF_NULL,                 \
      .StkSize = 256u,                        \
      .Prio = KERNEL_TMR_TASK_PRIO_DFLT,      \
      .RateHz = 40u                          \
    },                                        \
    .MemSeg = DEF_NULL,                       \
    .TickRate = 40u                          \
}

/*******************************************************************************
 ***************************  GLOBAL VARIABLES   *******************************
 ******************************************************************************/

#ifndef  OS_CFG_COMPAT_INIT
#if (RTOS_CFG_EXTERNALIZE_OPTIONAL_CFG_EN == DEF_ENABLED)
// Kernel configuration.
const OS_INIT_CFG OS_InitCfg = OS_INIT_CFG_DFLT;
#endif
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

static OS_TCB tcb;
static CPU_STK *stack;

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void xJavaTaskFunction(void *arg);

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  RTOS_ERR err;

  printf("Start\n");

  /* Print configuration of the Cortex-M33 Processor */
  printf("Cortex-M33 revision %X\n", __CM33_REV);

  /* Allocate the MicroJvm task stack */
  stack = (CPU_STK *)Mem_SegAlloc("MicroJvm Task Stack",
                                  OS_InitCfg.MemSeg,
                                  JAVA_TASK_STACK_SIZE * sizeof(CPU_STK),
                                  &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));

  /* Start MicroJvm task */
  OSTaskCreate(&tcb,
               "MicroJvm",
               xJavaTaskFunction,
               DEF_NULL,
               JAVA_TASK_PRIORITY,
               &stack[0],
               (JAVA_TASK_STACK_SIZE / 10u),
               JAVA_TASK_STACK_SIZE,
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CLR),
               &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}

/***************************************************************************//**
 * MicroJvm task.
 ******************************************************************************/
static void xJavaTaskFunction(void *arg)
{
  RTOS_ERR err;

  (void)arg;

  /* Start the VM */
  microej_main();

  /* Should reach this point only if the VM exits */
  OSTaskDel(&tcb,
            &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
}

/***************************************************************************//**
 * MicroJvm portage validation functions.
 ******************************************************************************/
#include "sni.h"
jfloat Java_com_is2t_microjvm_test_MJVMPortValidation_testFPU__FF (jfloat a, jfloat b) {return a * b;}
jdouble Java_com_is2t_microjvm_test_MJVMPortValidation_testFPU__DD (jdouble a, jdouble b) {return a * b;}
