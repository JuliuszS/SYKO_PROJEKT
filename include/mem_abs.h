#ifndef __MEM_ABS_H__
#define __MEM_ABS_H__

void dumpMEMConfiguration(void);

void loadCounter(char *file);

void loadPC(char *file);
void savePC(char *file);
void loadMEMC(char *file);
void loadMEMD(char *file);
void saveMEMD(char *file);
void saveCounter(char *file);
void loadCounter(char *file);

// Pobieranie pamieci
CodeType getMEMC(AddressType p);
DataType getMEMD(AddressType p);

// Operacje na PC
void setPC(AddressType v);
AddressType getPC(void);
// Pobieranie aktualnej instrukcji
CodeType getOpcode(void);

// Operacje na liczniku symulacji
CounterType getCounter(void);
void addCounter(CounterType n);

// Pobranie i zapis do rejestru
DataType getRegister(int n);
void setRegister(int n, DataType v);

// Sterowanie rejestrem flag
void setFlagsRegister(int b);
void resetFlagsRegister(int b);
int getFlagsRegister(int b);


// Definicje adresow i bitow rejestrow

//Bity SREG
#define FLAG_C                      0
#define FLAG_Z						1
#define FLAG_N						2
#define FLAG_V						3
#define FLAG_S						4
#define FLAG_H						5
#define FLAG_T						6
#define FLAG_I						7

// Stack pointer A_SPH A_SPL
#define A_SPL 0x3A
#define A_SPH 0x3B

//Rejestry Analog Comparatora

#define	ACSR_ADDRESS	0x50//Analog Comparator Control and Status Register
	#define	ACIS0 	0x01
	#define	ACIS1 	0x02
	#define	ACIC 	0x04
	#define	ACIE 	0x08
	#define	ACI 	0x10
	#define	ACO 	0x20
	#define	ACBG 	0x40
	#define	ACD 	0x80

#define DIDR1_ADDRESS	0x7F //Digital Input Disable Register 1
	#define AIN0D 0x00
	#define AIN1D 0x01

#endif //__MEM_ABS_H__

