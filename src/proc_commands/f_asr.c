#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_ASR(void){
    CodeType T = getOpcode();
    DataType Rd = (T & 0x1F0 )>>4;                 //identyfikacja numeru rejestru
	data = getRegister(Rd);
	
    printf("0x%04X[0x%04X]: ASR R%d\n", getPC(), getOpcode(), Rd);
	// C FLAG
    if(data&0x01)
        setFlagsRegister(FLAG_C);
    else
        resetFlagsRegister(FLAG_C);
	// N FLAG
	if(data&0x80)
        setFlagsRegister(FLAG_N);
    else
        resetFlagsRegister(FLAG_N); 
	// Z FLAG
	if(data>>1)
		resetFlagsRegister(FLAG_Z);
	else
        setFlagsRegister(FLAG_Z);
	
	// ************* to do ***************
	// V FLAG 
	if(data&0x01)
        setFlagsRegister(FLAG_V);
    else
        resetFlagsRegister(FLAG_V);
	// S FLAG
	if(data&0x01)
        setFlagsRegister(FLAG_S);  
    else
        resetFlagsRegister(FLAG_S);
	// *******************************************
	
    setRegister(Rd, data>>1);    //właściwe obliczenie

    setPC(getPC()+1);                                       //zwiększenie licznika rozkazów
    addCounter(1);
}
