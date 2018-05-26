#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_ADD(void){
    CodeType T = getOpcode();
    DataType Rr = (T & 0x000F)|((T&0x0200)>>5);    //identyfikacja numeru rejestru arg. 1
    DataType Rd = (T & 0x1F0 )>>4;                 //identyfikacja numeru rejestru arg. 2
	
	DataType R0 = 0;
	DataType R1 = 1;
	
	CodeType result = (getRegister(Rr)*getRegister(Rd)) % MAX_DATA_VAL;
	
    printf("0x%04X[0x%04X]: MUL R%d, R%d\n", getPC(), getOpcode(), Rd, Rr);

    if((result&0x8000)>>15 == 1)
        setFlagsRegister(FLAG_C);                           //ustawienie flagi przeniesienia
    else
        resetFlagsRegister(FLAG_C);	//wykasowanie flagi przeniesienia
    
	if(result == 0x0000)
        setFlagsRegister(FLAG_Z);                           //ustawienie flagi przeniesienia
    else
        resetFlagsRegister(FLAG_Z);
			
    setRegister(R0, result&0x00FF);    //wynik R0
	setRegister(R1, result&0xFF00);	  //wynik R1
	
    setPC(getPC()+1);                                       //zwiększenie licznika rozkazów
    addCounter(1);
}
