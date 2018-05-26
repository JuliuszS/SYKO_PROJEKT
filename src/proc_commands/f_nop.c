#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_NOP(void){
               
    printf("0x%04X[0x%04X]: NOP\n", getPC(), getOpcode());

    setPC(getPC()+1); //zwiększenie licznika rozkazów
    addCounter(1);
}