#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_ICALL(void){
    CodeType T = getOpcode();
    AddresType Z = ( getRegister(31)<<8 ) | getRegister(30);
	
    printf("0x%04X[0x%04X]: ICALL \n", getPC(), getOpcode());
		
    setPUSH_ADDRES(getPC()+1);
	setPC(Z);
	
    setPC(getPC()+1);   //zwiększenie licznika rozkazów
    addCounter(1);
}