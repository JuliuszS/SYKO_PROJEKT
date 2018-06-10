#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_CLI(void){
    // resetuj Interrupt Enable
	 resetFlagsRegister(FLAG_I);
	printf("0x%04X[0x%04X]: CLI \n", getPC(), getOpcode());
    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}
