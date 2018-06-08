#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_RETI(void){
	// Pobierz adres ze stosu
	AddressType NewAddres = getPOP_ADDRES();
	// Ustaw nowe PC
	setPC(NewAddres);
	 // Enable Global Interrupt
	 setFlagsRegister(FLAG_I);
    
	addCounter(1);
}