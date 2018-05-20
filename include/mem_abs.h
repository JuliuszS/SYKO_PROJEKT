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

#endif //__MEM_ABS_H__
