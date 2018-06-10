#include <stdio.h>
#include "types.h"
#include "mem_abs.h"

void F_NEG(void){
    CodeType T = getOpcode();
    DataType Rd = (T & 0x1F0 )>>4;      //identyfikacja numeru rejestru arg. 2
	
    printf("0x%04X[0x%04X]: NEG R%d\n", getPC(), getOpcode(), Rd);
	
	union bits result;
	result.sign	= 0 - (signed char)getRegister(Rd)-1;
	
	// H FLAG
	if((result.unsign&0x8)>>3 + (getRegister(Rd)&0x8)>>3)
       setFlagsRegister(FLAG_H);      
    else
	   resetFlagsRegister(FLAG_H);    
    // V FLAG
	if( 0x80 == result.unsign)
       setFlagsRegister(FLAG_V);    
    else
	   resetFlagsRegister(FLAG_V);   
    // N FLAG
    if( (0x80 & result.unsign)>>7)
       setFlagsRegister(FLAG_N);     
    else
	   resetFlagsRegister(FLAG_N); 
	// Z FLAG
    if(result.unsign == 0 )
       setFlagsRegister(FLAG_Z);    
    else
	   resetFlagsRegister(FLAG_Z);
    // C FLAG
    if( result.unsign != 0)
       setFlagsRegister(FLAG_C);
    else
	   resetFlagsRegister(FLAG_C);
   // S FLAG
    if(!( (getFlagsRegister(FLAG_N)>>FLAG_N) == (getFlagsRegister(FLAG_V)>>FLAG_V)))
       setFlagsRegister(FLAG_S);     
    else
	   resetFlagsRegister(FLAG_S); 
	
    setRegister(Rd, result.unsign);    //przypisanie

    setPC(getPC()+1);                          //zwiększenie licznika rozkazów
    addCounter(1);
}
