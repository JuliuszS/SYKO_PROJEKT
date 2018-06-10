#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_EOR(void){
    CodeType T = getOpcode();
    DataType Rr = (T & 0x000F)|((T&0x0200)>>5);    //identyfikacja numeru rejestru arg. 1
    DataType Rd = (T & 0x1F0 )>>4;                 //identyfikacja numeru rejestru arg. 2
	
    printf("0x%04X[0x%04X]: EOR R%d, R%d\n", getPC(), getOpcode(), Rd, Rr);
	
	DataType result = ((getRegister(Rr)^getRegister(Rd)) % MAX_DATA_VAL);
	

	// FLAGA N
	if(result&0x80)
	{
		setFlagsRegister(FLAG_N);
		setFlagsRegister(FLAG_S);
	}	
    else
	{
        resetFlagsRegister(FLAG_N); 
		resetFlagsRegister(FLAG_S); 
	}
	
	// Z FLAG
	if(result == 0)
        setFlagsRegister(FLAG_Z);               
    else
        resetFlagsRegister(FLAG_Z); 
	
	// Flaga V
	resetFlagsRegister(FLAG_V); 
          
    setRegister(Rd, result);    //właściwe obliczenie

    setPC(getPC()+1);                                       //zwiększenie licznika rozkazów
    addCounter(1);
}
