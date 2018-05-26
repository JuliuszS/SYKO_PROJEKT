#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "mem_abs.h"
#include "interpreter.h"
#include "interrupt.h"

// Nieznana instrukcja
void NoInstr(void);

// deklaracje F_Gx()
void F_G1(void);
void F_G2(void);
void F_G3(void);
void F_G10(void);
void F_G13(void);

//naglowki poszczegolnych opcodow 
void F_ADD(void);
void F_JMP(void);
void F_RJMP(void);
void F_NOP(void);
//...


void doInstr(CodeType T){
    switch((T & 0xF000)>>12){   //wy³uskanie w³aœciwego kodu operacji (4 najwyzsze bity)
	   case ID_G1:
			F_G1();
			break;
   	   case ID_G2:       
            F_G2();
            break;
        case ID_G3:   
            F_G3();
            break;
        case ID_G10:        
            F_G10();
            break;
        case ID_G13:   
			// Tylko RJMP ma takie ID		
            F_RJMP();
            break;	
		
        default:
			printf("doInstr: ");
			NoInstr(); // exit  
    }
}

void NoInstr(void)
{
	printf("---------------------------------------------------------\r\n");
	printf("Wykryto nieznana instrukcje (PC=0x%08lx, T=0x%04lx)\r\n", getPC(), getOpcode());
    saveCPUState();
    exit(-1);
}

void F_G1(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 
	 if( (T & ADD_MASK) == ADD_VAL ) 
		F_ADD();	// ADD
	 else
		if(T == 0x0000) F_NOP(); // NOP
	 else
		NoInstr();
	 
}

void F_G2(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 NoInstr();
}

void F_G3(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 NoInstr();
}

void F_G10(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 if(T&JMP_MASK == JMP_VAL) F_JMP();
	 else NoInstr();
	 
}

void F_G13(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 NoInstr();
}






