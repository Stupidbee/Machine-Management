
#include "stdint.h"

__asm void HardFault_Handler(void)
{
	IMPORT HardFault_Handler_c
	TST LR, #4
	ITE EQ
	MRSEQ R0, MSP
	MRSNE R0, PSP
	B HardFault_Handler_c
}

void HardFault_Handler_c(uint32_t * hardfault_args)
{
	while(1);	
}
