#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_RETI(void){
	CodeType T = getOpcode();
	
    printf("0x%04X[0x%04X]: RETI\n", getPC(), getOpcode());
	// Pobierz adres ze stosu
	AddressType NewAddres = getPOP_ADDRES();
	// Ustaw nowe PC
	setPC(NewAddres-1);
	 // Enable Global Interrupt
	 setFlagsRegister(FLAG_I);
    
	addCounter(1);
}