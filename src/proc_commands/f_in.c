#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_IN(void){
    CodeType T = getOpcode();
    DataType Rd = (T & 0x1F0 )>>4;    //identyfikacja numeru rejestru arg
    CodeType A = (T & 0x000F)|((T&0x0600)>>5);  //identyfikacja numeru rejestru IO
	
    printf("0x%04X[0x%04X]: IN R%d, %d\n", getPC(), getOpcode(), Rd,A);
        
	setRegister(Rd, getIORegister(A));
	
    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}
