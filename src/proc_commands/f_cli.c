#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_SEI(void){
    // resetuj Interrupt Enable
	 resetFlagsRegister(FLAG_I);
	
    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}
