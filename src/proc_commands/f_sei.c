#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_SEI(void){
    // USTAW G_interrupt
	 setFlagsRegister(FLAG_I);
	
    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}
