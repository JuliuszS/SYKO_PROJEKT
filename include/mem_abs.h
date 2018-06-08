#ifndef __MEM_ABS_H__
#define __MEM_ABS_H__

#include "types.h"

#define FILE_COUNTER            "test/file_counter.bin"
#define FILE_PC                 "test/file_pc.bin"
#define FILE_DATA               "test/file_data.bin"
#define FILE_CODE               "test/file_code.bin"

//********************************************************
//
// Definicje adresow i bitow rejestrow
//
//********************************************************

//Bity SREG
#define FLAG_C                      0
#define FLAG_Z						1
#define FLAG_N						2
#define FLAG_V						3
#define FLAG_S						4
#define FLAG_H						5
#define FLAG_T						6
#define FLAG_I						7

//********************************
//
// Stack pointer A_SPH A_SPL
// ADRES I/O
//
//********************************
#define A_SPL 0x3D
#define A_SPH 0x3E

//********************************
//
// Rejestry Analog Comparatora
//
//********************************
#define	A_ACSR_ADDRESS	0x30//Analog Comparator Control and Status Register
	#define	ACIS0 	0x01
	#define	ACIS1 	0x02
	#define	ACIC 	0x04
	#define	ACIE 	0x08
	#define	ACI 	0x10
	#define	ACO 	0x20
	#define	ACBG 	0x40
	#define	ACD 	0x80

#define ADCSRA_ADDRESS 0x7A
	#define ADEN 0x80
#define ADCSRB_ADDRESS 0x7b
	#define ACME 0x40
#define ADMUX_ADDRESS 0x7C
	
#define DIDR1_ADDRESS	0x7F //Digital Input Disable Register 1
	#define AIN0D 0x00
	#define AIN1D 0x01

//*********************************
//
// Deklaracje funkcji
//
//*********************************	

// Wyświetlanie danych o pamieci
void dumpMEMConfiguration(void);
void saveCPUState(void);
void loadCounter(char *file);

// Ładowanie i zapis pamieci
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
void setCounter(CounterType new_val);
void addCounter(CounterType n);

// Pobranie i zapis do rejestru
DataType getRegister(int n);
void setRegister(int n, DataType v);

// Sterowanie rejestrem flag
void setFlagsRegister(int b);
void resetFlagsRegister(int b);
DataType getFlagsRegister(int b);

// Zapis do pamieci
void setMEMD(DataType d,AddressType p);

// Stack Pionter
void setSP(AddressType v);
AddressType getSP(void);

// Operacje na stosie
DataType getPOP(void);
void setPUSH(DataType d);

// Operacje na stosie zapis adresu(2 bajty)
void setPUSH_ADDRES(AddressType adr);
AddressType getPOP_ADDRES(void);

// Operacje na rejestrach IO
DataType getIORegister(int n);
void setIORegister(int n, DataType v);

#endif //__MEM_ABS_H__


























