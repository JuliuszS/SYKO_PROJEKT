#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_STS(void){
    CodeType T = getOpcode();
    DataType Rr = (T & 0x1F0 )>>4;    //identyfikacja numeru rejestru arg
    setPC(getPC()+1);
	AddressType K = getOpcode();  //identyfikacja numeru rejestru IO
	
    printf("0x%04X[0x%04X]: STS %d, R%d\n", getPC(), getOpcode(), K, Rr);
	
    setMEMD(getRegister(Rr), K);
 
    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}
