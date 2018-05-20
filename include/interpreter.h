#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

void doInstr(CodeType T);

// INSTR OPCODES
#define LDD_SDD_MASK 0xD208
#define ID_LDD_Z 	 0x8000
#define ID_LDD_Y 	 0x8008  
#define ID_STD_Z 	 0x8200 
#define ID_STD_Y 	 0x0008  

// najstarsze 4 bity opcode
  
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




#endif //__INTERPRETER_H__
