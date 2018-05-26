#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

void doInstr(CodeType T);

// ************** INSTR OPCODES **************
/* !! Te instrukcje maja argumenty w 4 pierwszych bitach 
	 dlatego sa tu oddzielnie zdefiniowane !! */
#define LDD_SDD_MASK 0xD208
#define ID_LDD_Z 	 0x8000
#define ID_LDD_Y 	 0x8008  
#define ID_STD_Z 	 0x8200 
#define ID_STD_Y 	 0x0008  

//************** najstarsze 4 bity opcode -> 16 mozliwosci **************
  
#define ID_G1  0b0000 
//NOP !
//ADD !
//SBC
#define ID_G2  0b0001 
//ADC
//SUB !
#define ID_G3  0b0010 
//EOR	!!!
//OR !
//MOV !
//AND !
#define ID_G4  0b0011 
#define ID_G5  0b0100
#define ID_G6  0b0101
#define ID_G7  0b0110
#define ID_G8  0b0111
#define ID_G9  0b1000
#define ID_G10 0b1001
//LPM 	!!!
//ICALL !!!
//MUL 	!!!
//NEG 	!!! 
//ASR 	!!!
//RETI - interrupt niepotrzebne
//RET
//CALL
//JMP
//DEC
//INC
//PUSH
//POP
#define ID_G11 0b1011
#define ID_G12 0b1100
#define ID_G13 0b1101
//RCALL !!!
#define ID_G14 0b1110
#define ID_G15 0b1111

// ************* Intr OP MASK and VAL defitions **************
#define ADD_MASK 0x0c00
#define ADD_VAL  0x0c00

#define RJMP_MASK NN
#define RJMP_VAL NN

#define JMP_MASK 0x070e
#define JMP_VAL  0x040c

#define MOV_MASK  0x0c00
#define MOV_VAL	  0x0c00
//MOV !
#define EOR_MASK 0x0c00
#define EOR_VAL  0x0400
//EOR	!!! 
#define LPM_MASK
#define LPM_VAL
//LPM 	!!!
#define ICALL_MASK 0x000f
#define ICALL_VAL  0x0009
//ICALL !!!
#define MUL_MASK 0x0c00
#define MUL_VAL  0x0c00
//MUL 	!!!
#define NEG_MASK 0x000f
#define NEG_VAL  0x0001
//NEG 	!!!
#define ASR_MASK 0x000f
#define ASR_VAL  0x0005
//ASR 	!!!










#endif //__INTERPRETER_H__
