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
void F_G12(void);

//naglowki poszczegolnych opcodow 
void F_ADD(void);
void F_JMP(void);
void F_RJMP(void);
void F_NOP(void);
//... TO DO INSTR
void F_MOV(void);
void F_EOR(void);
void F_ICALL(void);
void F_MUL(void);
void F_NEG(void);
void F_ASR(void);
void F_RCALL(void);


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
		case ID_G12:
			F_RJMP();
			break;
        case ID_G13:   		
			//F_RCALL();
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
	 if(T&MOV_MASK == MOV_VAL)
		F_MOV();
	 else 
		 if(T&EOR_MASK == EOR_VAL) F_EOR();
	 else
		 NoInstr();
}

void F_G10(void)
{
	 CodeType T=getOpcode() & 0x0FFF;
	 if(T&JMP_MASK == JMP_VAL) 
		 F_JMP();
	 else 
		 if(T&ICALL_MASK == ICALL_VAL);// F_ICALL();
	 else 
		 if(T&MUL_MASK == MUL_VAL) F_MUL();
	 else 
		 if(T&NEG_MASK == NEG_VAL) F_NEG();
	 else 
		 if(T&ASR_MASK == ASR_VAL) F_ASR();
	 else
		NoInstr();
	 
}







