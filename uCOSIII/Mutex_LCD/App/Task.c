/**
  ******************************************************************************
  * @file    Task.c
  * @author  Huang ying xin
  * @version V1.0.0
  * @date    14-January-2014
  * @brief   This file is used to creat the task. 
	*/
#include <os.h>
#include <stm32f4xx.h>
#include <stdio.h>
#include "Task.h"
#include "stm324x9i_eval.h"
#include "lcd_log.h"
   
OS_TCB   Task_ATCB;
CPU_STK  Task_AStk[TASK_A_STK_SIZE];
extern OS_MUTEX SerialMutex;

void Task_A(void *p_arg)
{	   
	OS_ERR err;
	CPU_TS ts;

	while(DEF_TRUE)
	{
		OSMutexPend(&SerialMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
		BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		BSP_LCD_DisplayStringAtLine(5, (uint8_t *)"Task A is runing ");
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)"Task B is waiting");
		OSTimeDly(400, OS_OPT_TIME_DLY, &err); 
		OSMutexPost(&SerialMutex, OS_OPT_POST_NONE, &err);
	}
}

OS_TCB   Task_BTCB;
CPU_STK  Task_BStk[TASK_B_STK_SIZE];

void Task_B(void *p_arg)
{			  
	OS_ERR  err;
	CPU_TS  ts;

	while(DEF_TRUE)
	{
		OSMutexPend(&SerialMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DisplayStringAtLine(5, (uint8_t *)"Task A is waiting");
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)"Task B is runing ");
		OSTimeDly(400, OS_OPT_TIME_DLY, &err);	
		OSMutexPost(&SerialMutex, OS_OPT_POST_NONE, &err);
	}
}
