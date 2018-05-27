#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_LDI(void){
    CodeType T = getOpcode();
    DataType K =  ((T & 0x0F00)>>4)|(T&0x000F);     //identyfikacja numeru rejestru arg
    DataType Rd = (T & 0x00F0)>>4;  //identyfikacja numeru rejestru IO
	
    printf("0x%04X[0x%04X]: LDI $R%d, $%d\n", getPC(), getOpcode(), Rd, K);
        
    setRegister(Rd, K);    //właściwe obliczenie

    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}
