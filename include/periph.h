#ifndef __PERIPH_H__
#define __PERIPH_H__

#include "types.h"

// Liczba pinów
#define NUMBERS_OF_PINS 28 // DIP 28

// Pliki perypetiow
#define FILE_PERIPH 			"test/file_periph.txt"
#define FILE_PERIPH_CURRENT		"test/file_current_p.bin"


//***********************************
//
// Definicje numerów pinów
//
//***********************************
// Założona obudowa 28-pin PDIP

#define AIN0 12
#define AIN1 13

#define ADC0 23
#define ADC1 24
#define ADC2 25
#define ADC3 26
#define ADC4 27
#define ADC5 28
// BRAK W PDIP 28
#define ADC6 0
#define ADC7 0


// Ładowanie wartości napięcia na pinach
void loadPeriphCurrent(char *file);
void savePeriphCurrent(char *file);
void loadPeriph(char *file);
void printfPeriphTab(void);

// Pobierz napiecie na pinie
float getPinVal(int pin_number); 

// Działanie sprzętowych modułów
void do_periph(CounterType time);
void do_AnalogComparator(void);
void do_AnalogComparator_SelectInput(float *IN1,float *IN2);
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
// Zamienia stringa na strukture zmiany stanu pinu
struct PinState strtoPinStruct(char* line);
// Sortowanie stosu zmian 
void periphStackTimeSort(void);
// Porównanie czasów zmian
int time_compare(const void *,const void *);
// Błąd ładowania danych
void loadPeriph_ERROR(char* info);
// Wypisz obecny stan na pinach
void printfPinsCurrentValTab(void);

#endif