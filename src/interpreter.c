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
//...

//wzorce opcodow 
#define ID_ADD_R1_R2            0x01
#define ID_ADD_R1_MEM_R2        0x02
#define ID_JMP_MEMC             0x03
#define ID_JMP_REL              0x04
//...


void doInstr(CodeType T){
    switch((T & 0xF000)>>12){   //wy³uskanie w³aœciwego kodu operacji (4 najwyzsze bity)
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
        //...
        default:
            printf("Wykryto nieznana instrukcje (PC=0x%08lx, T=0x%04lx)\r\n", getPC(), T);
            saveCPUState();
            exit(-1);
    }
}
