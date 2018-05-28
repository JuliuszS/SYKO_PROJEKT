#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_RCALL(void){
    CodeType T = getOpcode();
    AddressType K = T&(0x0FFF);
	AddressType NewAddres;
	
	if(K&0x0800)
	{
		// K jest ujemne
		NewAddres = (getPC() + (K&0x07FF) + 1) - 0x0800;
		printf("0x%04X[0x%04X]: RCALL PC %d \n", getPC(), getOpcode(), (signed short)((K&0x07FF) + 1) - 0x0800);
	}
	else
	{
		// K jest dodatnie
		NewAddres = getPC() + (K&0x07FF);
		printf("0x%04X[0x%04X]: RCALL PC +%d \n", getPC(), getOpcode(), K&0x07FF);
	}	
		
    setPUSH_ADDRES(getPC()+1);
	setPC(NewAddres);
	
    addCounter(1);
}