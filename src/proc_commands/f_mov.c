#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_MOV(void){
	CodeType T = getOpcode();
    DataType Rr = (T & 0x000F)|((T&0x0200)>>5); //identyfikacja numeru rejestru arg. 1
    DataType Rd = (T & 0x1F0 )>>4;              //identyfikacja numeru rejestru arg. 2

    printf("0x%04X[0x%04X]: MOV R%d, R%d\n", getPC(), getOpcode(), Rd, Rr);
    
    setRegister(Rd, Rr);  //właściwe przypisanie

    setPC(getPC()+1);     //zwiększenie licznika rozkazów
    addCounter(1);
}
