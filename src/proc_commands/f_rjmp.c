#include <stdio.h>
#include "types.h"
#include "mem_abs.h"
#include "stdint.h"
void F_RJMP(void){
	CodeType jmp_val = getOpcode() & 0x0FFF; 
	
    if((getOpcode() & 0x0800)==0)
	{
		printf("0x%04X[0x%04X]: RJMP PC+%d\n", getPC(), getOpcode(), jmp_val+1);
		setPC(getPC()+jmp_val+1);
	}
    else
	{
		printf("0x%04X[0x%04X]: RJMP PC%+d\n", getPC(), getOpcode(), -0x0800 + (jmp_val&0x7FF)+1 );
		setPC( getPC() + (-0x0800 + (jmp_val&0x7FF))+1 );
	}

    addCounter(1);
}
