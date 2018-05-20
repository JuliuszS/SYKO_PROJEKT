#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "mem_abs.h"
#include "interpreter.h"
#include "interrupt.h"

// deklaracje F_Gx()
void F_G1(void);
void F_G2(void);
void F_G2(void);
void F_G10(void);
void F_G13(void);

//naglowki poszczegolnych opcodow 
void F_ADD1(void);
void F_ADD2(void);
void F_JMP_MEMC(void);
void F_JMP_REL(void);
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
            F_G13();
            break;	
		
        default:
            printf("Wykryto nieznana instrukcje (PC=0x%08lx, T=0x%04lx)\r\n", getPC(), T);
            saveCPUState();
            exit(-1);
    }
}

void F_G1(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 
	 //if(T == 0) ;//NOP;
	 //else if(T == ADD_MASK) //ADD;
	 //else if(T == SBC_MASK) //SBC_MASK
}

void F_G2(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 
}

void F_G2(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 
}

void F_G10(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 
}

void F_G13(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 
}






