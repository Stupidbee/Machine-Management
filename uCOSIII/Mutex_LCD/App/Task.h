
#ifndef _APP_TASK_H_
#define _APP_TASK_H_

#include <os.h>

#define TASK_A_STK_SIZE	1000
#define TASK_B_STK_SIZE	1000

#define TASK_A_PRI			4
#define TASK_B_PRI			5

extern OS_TCB   Task_ATCB;
extern CPU_STK  Task_AStk[TASK_A_STK_SIZE];

extern OS_TCB   Task_BTCB;
extern CPU_STK  Task_BStk[TASK_A_STK_SIZE];


void Task_A(void *p_arg);
void Task_B(void *p_arg);


#endif
