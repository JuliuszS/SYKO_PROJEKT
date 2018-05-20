#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "mem_abs.h"
#include "interpreter.h"
#include "interrupt.h"

//naglowki poszczegolnych opcodow 
void F_ADD1(void);
void F_ADD2(void);
void F_JMP_MEMC(void);
void F_JMP_REL(void);

//ID_LPM_R0_Z		
//ID_LPM_Rd_Z		
//ID_ICALL_Z		
//ID_RCALL_K		
//ID_MUL_Rd_Rr	
//ID_NEG_Rd								T
//ID_EOR_Rd_Rr	
//ID_ASR_Rd		

//...

// wzorce opcodow 
#define ID_ADD_R1_R2_CARRY      0x00 //TO DO
#define ID_ADD_R1_R2            0x01
#define ID_ADD_R1_MEM_R2        0x02
#define ID_JMP_MEMC             0x03
#define ID_JMP_REL              0x04
//...

// Instrukcje z zadania
#define ID_GROUP_0B1001 // 0x09
	#define ID_LPM_R0_Z		0b1001	//LOAD PROGRAM MEMORY to R0				TODO
	#define ID_LPM_Rd_Z		0b1001	//LOAD PROGRAM MEMORY to Rd 			TODO
	#define ID_ICALL_Z		0b1001	//Extended Indirect Call to Subroutine	TODO
	#define ID_MUL_Rd_Rr	0b1001	//Multiply Unsigned						TODO
	#define ID_NEG_Rd		0b1001	//Two Complement						TODO
	#define ID_ASR_Rd		0b1001  //Arithmetic Shift Right				TODO

#define ID_RCALL_K		0b1101	//Relative Call Subroutine				TODO
#define ID_EOR_Rd_Rr	0b0010	//OR logic operation					TODO



void doInstr(CodeType T){
    switch((T & 0xF000)>>12){   //wy³uskanie w³aœciwego kodu operacji (4 najwyzsze bity)
		case ID_ADD_R1_R2_CARRY:
			//TO DO !!!!
			break;
   	   case ID_ADD_R1_R2:       //wywolac instrukcje ADD R1,R2
            F_ADD1();
            break;
        case ID_ADD_R1_MEM_R2:   //wywolac instrukcje ADD R1,[R2]
            F_ADD2();
            break;
        case ID_JMP_MEMC:        //wywolac instrukcje JMP MEM
            F_JMP_MEMC();
            break;
        case ID_JMP_REL:         //wywolac instrukcje JMP REL
            F_JMP_REL();
            break;
		case ID_GROUP_0B1001:
			// TO DO F_OBIOOI();
			break;	
        //...
		
        default:
            printf("Wykryto nieznana instrukcje (PC=0x%08lx, T=0x%04lx)\r\n", getPC(), T);
            saveCPUState();
            exit(-1);
    }
}
