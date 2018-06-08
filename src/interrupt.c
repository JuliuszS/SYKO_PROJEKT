#include <stdio.h>
#include "types.h"
#include "interrupt.h"
#include "mem_abs.h"


//****************************************
//
//	Sprawdź przerwanie
//
//****************************************
void checkInterrupt(void){
	getFlagsRegister(FLAG_I);
	
	// Sprawdzenie global interrupt enable
	if(getFlagsRegister(FLAG_I)){ 
		/* Kolejność funkcji wyznacza priorytet przerwań 
			0 - przerwanie , 1 - brak przerwania*/
			
		if(checkAC_Interrupt());
		//else 
		//if(check_jakies_tam_przerwanie());
		//else
		//... itd i mamy zaimplementowane priorytety przerwań
	}
	
}

//*******************************
//
// Sprawdzenie przerwania AC 
//
//******************************
int checkAC_Interrupt(void){
	DataType ACSR = getIORegister(A_ACSR_ADDRESS);	
	AddressType adr;
	
	// Zachodzi przerwanie
	if( (ACSR&ACIE) && ACSR&ACI)
	{
		printf("AC Interrupt:\n");
		// Wepchnij na stos adres powrotu
		setPUSH_ADDRES(getPC()+1);
		
		// ustaw nowy PC na wektor przerwania
		setPC(AC_VECTOR);
		
		// Reset flagi przerwania AC
		setIORegister(A_ACSR_ADDRESS, getIORegister(A_ACSR_ADDRESS) & (~ACI));
		
		// Reset flagi przerwania globalnego
		resetFlagsRegister(FLAG_I);
		return 0; // Przerwanie	
	}
	
	return 1;	// Brak przerwania
}
