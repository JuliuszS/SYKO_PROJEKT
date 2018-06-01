#ifndef __PERIPH_H__
#define __PERIPH_H__

#include "types.h"

#define NUMBERS_OF_PINS 38

// Ładowanie wartości napięcia na pinach
void loadPeriph(char *file);
void printfPeriphTab(void);
// Działanie sprzętowych modułów
void do_periph(CounterType time);
void do_AnalogComparator(void);

// -------- STOS ---------------
// Czy stos pusty
int periphIsStackEmpty(void);
// Zwolnij stos
void periphFree(void);
// Pobierz stempel czasowy najwyższej struktury na stosie
CounterType getFirstElementTime(void);
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