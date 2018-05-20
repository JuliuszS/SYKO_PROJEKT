#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_JMP_MEMC(void){
    printf("0x%04X[0x%04X]: JMP MEMC[0x%04X]=0x%04X\n", getPC(), getOpcode(), getPC()+1, getMEMC(getPC()+1));

    setPC(getMEMC(getPC()+1));

    addCounter(1);
}
