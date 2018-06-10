#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_SEI(void){
    CodeType T = getOpcode();
	
    printf("0x%04X[0x%04X]: SEI\n", getPC(), getOpcode());
	
	// USTAW G_interrupt
	 setFlagsRegister(FLAG_I);
	
    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}
