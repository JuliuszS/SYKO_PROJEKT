#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_RCALL(void){
    CodeType T = getOpcode();
    CodeType jmp_val = T&0x0FFF;
	AddressType NewAddres;
	
	if((T&0x0800)==0)
	{
		// K jest ujemne
		NewAddres = getPC()+jmp_val+1;
		printf("0x%04X[0x%04X]: RCALL PC %+d \n", getPC(), getOpcode(), jmp_val+1);
	}
	else
	{
		// K jest dodatnie
		NewAddres = getPC() + (-0x0800 + (jmp_val&0x7FF))+1;
		printf("0x%04X[0x%04X]: RCALL PC %+d \n", getPC(), getOpcode(), (-0x0800 + (jmp_val&0x7FF))+1);
	}	
		
    setPUSH_ADDRES(getPC()+1);
	setPC(NewAddres);
	
    addCounter(1);
}