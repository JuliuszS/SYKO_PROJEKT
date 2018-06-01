#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

void doInstr(CodeType T);

// ************** INSTR OPCODES **************
/* !! Te instrukcje maja argumenty w 4 pierwszych bitach 
	 dlatego sa tu oddzielnie zdefiniowane !! */
	 // NIE ZAIMPLEMENTOWANE BO NIE TRZEBA BYŁO
#define LDD_SDD_MASK 0xD208
#define ID_LDD_Z 	 0x8000
#define ID_LDD_Y 	 0x8008  
#define ID_STD_Z 	 0x8200 
#define ID_STD_Y 	 0x0008  

//************** najstarsze 4 bity opcode -> 16 mozliwosci **************
  
#define ID_G1  0b0000 
#define ID_G2  0b0001 
#define ID_G3  0b0010 
#define ID_G4  0b0011 
#define ID_G5  0b0100
#define ID_G6  0b0101
#define ID_G7  0b0110
#define ID_G8  0b0111
#define ID_G9  0b1000
#define ID_G10 0b1001
#define ID_G11 0b1011
#define ID_G12 0b1100
#define ID_G13 0b1101
#define ID_G14 0b1110
#define ID_G15 0b1111

// ************* Intr OP MASK and VAL defitions **************
// NN oznacza że pierwsze 4 bity definiują instrukcję

#define ADD_MASK 0x0c00 
#define ADD_VAL  0x0c00

#define RJMP_MASK NN 
#define RJMP_VAL NN

#define JMP_MASK 0x0e0e 
#define JMP_VAL  0x040c

#define MOV_MASK  0x0c00
#define MOV_VAL	  0x0c00

#define EOR_MASK 0x0c00
#define EOR_VAL  0x0400

#define LPM_MASK NN
#define LPM_VAL NN

#define ICALL_MASK 0x0fff
#define ICALL_VAL  0x0509

#define MUL_MASK 0x0c00
#define MUL_VAL  0x0c00

#define NEG_MASK 0x000f
#define NEG_VAL  0x0001

#define ASR_MASK 0x000f
#define ASR_VAL  0x0005

#define OUT_MASK 0x0800
#define OUT_VAL  0x0800

#define LDI_MASK NN
#define LDI_VAL  NN











#endif //__INTERPRETER_H__
