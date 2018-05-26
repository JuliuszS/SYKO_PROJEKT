#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_ADD(void){
    CodeType T = getOpcode();
    DataType Rr = (T & 0x000F)|((T&0x0200)>>5);    //identyfikacja numeru rejestru arg. 1
    DataType Rd = (T & 0x1F0 )>>4;                 //identyfikacja numeru rejestru arg. 2
	
    printf("0x%04X[0x%04X]: ADD R%d, R%d\n", getPC(), getOpcode(), Rd, Rr);

    if((getRegister(Rd) + getRegister(Rr)) > MAX_DATA_VAL)
        setFlagsRegister(FLAG_C);                           //ustawienie flagi przeniesienia
    else
        resetFlagsRegister(FLAG_C);                         //wykasowanie flagi przeniesienia
        
    setRegister(Rd, (getRegister(Rr) + getRegister(Rd)) % MAX_DATA_VAL);    //w³aœciwe obliczenie

    setPC(getPC()+1);                                       //zwiêkszenie licznika rozkazów
    addCounter(1);
}
