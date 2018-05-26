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
	//NOP GOTOWE
	//ADD GOTOWE
	//SBC
#define ID_G2  0b0001 
	//ADC
	//SUB !
#define ID_G3  0b0010 
	//EOR// DEK
	//OR !
	//MOV// DEK
	//AND !
#define ID_G4  0b0011 
#define ID_G5  0b0100
#define ID_G6  0b0101
#define ID_G7  0b0110
#define ID_G8  0b0111
#define ID_G9  0b1000
#define ID_G10 0b1001
	//LPM 	!!!
	//ICALL !!! //dec
	//MUL 	!!! //dec
	//NEG 	!!! //dec
	//ASR 	!!! //dec
	//RETI - interrupt niepotrzebne
	//RET
	//CALL
	//JMP // GOTOWE
	//DEC
	//INC
	//PUSH
	//POP
#define ID_G11 0b1011
#define ID_G12 0b1100
#define ID_G13 0b1101
	//RCALL !!! //dec
#define ID_G14 0b1110
#define ID_G15 0b1111

// ************* Intr OP MASK and VAL defitions **************
#define ADD_MASK 0x0c00 // gotowa
#define ADD_VAL  0x0c00

#define RJMP_MASK NN // gotowa
#define RJMP_VAL NN

#define JMP_MASK 0x0e0e // gotowa
#define JMP_VAL  0x040c

#define MOV_MASK  0x0c00
#define MOV_VAL	  0x0c00

#define EOR_MASK 0x0c00
#define EOR_VAL  0x0400

#define LPM_MASK
#define LPM_VAL

#define ICALL_MASK 0x000f
#define ICALL_VAL  0x0009

#define MUL_MASK 0x0c00
#define MUL_VAL  0x0c00

#define NEG_MASK 0x000f
#define NEG_VAL  0x0001

#define ASR_MASK 0x000f
#define ASR_VAL  0x0005











#endif //__INTERPRETER_H__
