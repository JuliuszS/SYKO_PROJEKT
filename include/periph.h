#ifndef __PERIPH_H__
#define __PERIPH_H__

#include "types.h"



// Ładowanie wartości napięcia na pinach
void loadPeriph(char *file);
void printfPeriphTab(void);
// Działanie sprzętowych modułów
void do_periph(void);

// -------- STOS ---------------
// Zwolnij stos
void periphFree(void);

// Nowy wskaznik
void periphNewPtr(struct PinState* New_ptr);

// Odejmij el
struct PinState periphPULL(void);

// Dodaj nowy el 
void periphPUSH(struct PinState state);
// -----------------------------
struct PinState strtoPinStruct(char* line);
void periphStackTimeSort(void);
int time_compare(const void *,const void *);
void loadPeriph_ERROR(char* info);

#endif