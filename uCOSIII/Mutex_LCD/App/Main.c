/**
  ******************************************************************************
  * @file    main.c
  * @author  Huang ying xin
  * @version V1.0.0
  * @date    14-January-2014
  * @brief   This file is main entrance for the C source. 
	*/
#include <stm32f4xx.h>
#include <os.h>
#include <stdio.h>
#include "bsp.h"
#include "lib_math.h"
#include "arm_math.h"
#include "stm324x9i_eval.h"
#include "Task.h"
#include "main.h"

#define TASK_STARTUP_STK_SIZE  	1000
#define TASK_STARTUP_PRI				2

OS_MUTEX SerialMutex;

//Task TCB table
OS_TCB   Task_StartupTCB;
//Task stack
CPU_STK  Task_StartupStk[TASK_STARTUP_STK_SIZE];

void Task_StartUp(void *p_arg)
{
	//Record error for uCOS
	OS_ERR  err;
	
	//Create a mutex at the beginning 
	OSMutexCreate(&SerialMutex, "Serial Mutex", &err);

	//Board Initialization
	BSP_Init();

	//Initialize the clock for uCOS
	OS_CPU_SysTickInit(SystemCoreClock/OSCfg_TickRate_Hz);
	
	//Initialize memory managment module
//	Mem_Init();

	// Compute CPU capacity with no task running
	#if OS_CFG_STAT_TASK_EN > 0u
	   OSStatTaskCPUUsageInit(&err);
	#endif
	
	//Shutdown interrupted time
	#ifdef CPU_CFG_INT_DIS_MEAS_EN
	    CPU_IntDisMeasMaxCurReset();
	#endif

	/*
	Task sample
	OSTaskCreate((OS_TCB       *)&Task_XXXTCB,
                 (CPU_CHAR     *)"TaskXXX",
                 (OS_TASK_PTR   )Task_XXX, 
                 (void         *)0,
                 (OS_PRIO       )TASK_XXX_PRI,
                 (CPU_STK      *)&Task_XXXStk[0],
                 (CPU_STK_SIZE  )TASK_XXX_STK_SIZE / 10,
                 (CPU_STK_SIZE  )TASK_XXX_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
	*/
	//Create task A and B
	OSTaskCreate((OS_TCB       *)&Task_ATCB,
                 (CPU_CHAR     *)"Task_A",
                 (OS_TASK_PTR   )Task_A, 
                 (void         *)0,
                 (OS_PRIO       )TASK_A_PRI,
                 (CPU_STK      *)&Task_AStk[0],
                 (CPU_STK_SIZE  )TASK_A_STK_SIZE / 10,
                 (CPU_STK_SIZE  )TASK_A_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
	
	OSTaskCreate((OS_TCB       *)&Task_BTCB,
                 (CPU_CHAR     *)"Task_B",
                 (OS_TASK_PTR   )Task_B, 
                 (void         *)0,
                 (OS_PRIO       )TASK_B_PRI,
                 (CPU_STK      *)&Task_BStk[0],
                 (CPU_STK_SIZE  )TASK_B_STK_SIZE / 10,
                 (CPU_STK_SIZE  )TASK_B_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
		  
	while (DEF_TRUE){
		OSTimeDlyHMSM(	0,	// hours 
										0,	// minutes 
										0, 	// seconds
										100,// milliseconds
										OS_OPT_TIME_HMSM_STRICT,
										&err
								 );
		//Add a led toggle here to mean that the system are runing
//		STM_EVAL_LEDToggle(LED1);
	}
}

int main(void)
{
	//Record error for uCOS
	OS_ERR  err;

	//Close all the interrupt
	CPU_IntDisable();

	//Initialize uCOS
	OSInit(&err);

	//Create a task
	OSTaskCreate((OS_TCB       *)&Task_StartupTCB,  
                 (CPU_CHAR     *)"TaskStartup",
                 (OS_TASK_PTR   )Task_StartUp, 
                 (void         *)0,
                 (OS_PRIO       )TASK_STARTUP_PRI,
                 (CPU_STK      *)&Task_StartupStk[0],
                 (CPU_STK_SIZE  )TASK_STARTUP_STK_SIZE / 10,
                 (CPU_STK_SIZE  )TASK_STARTUP_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	//Start Task
	OSStart(&err);
}
