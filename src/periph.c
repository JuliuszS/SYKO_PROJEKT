#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "types.h"
#include "periph.h"
#include "mem_abs.h"

#define MAX_LINE_SIZE 30 
#define SEPARATOR ','

/*
	!!! 
	Zmiany stanow pinow sa przechowywane wg
    czasowego ich wystepowania, na stosie w 
	postaci struktur zawierajacych czas pin 
	oraz wartość docelowa na pinie. Obecny stanow
	jest przechowywany w oddzielnej tablicy
*/



//**********************************************
//
// DEKLARACJA STOSU I TABLICY STANU
//
//**********************************************

// Tablica stanu
float PinsCurrentVal[NUMBERS_OF_PINS];
// Stos
struct PinState * PinsTabChange = NULL;
int PinsTabStack;
int PinsTabSize;

//**********************************************
//
// Zwolnij wskaznik na stos
//
//**********************************************

void periphFree(void)
{
	if(PinsTabChange != NULL) free(PinsTabChange);
	PinsTabChange = NULL;
}

//**********************************************
//
// Nowy wskaznik na stos
//
//**********************************************

void periphNewPtr(struct PinState* New_ptr)
{
	if(PinsTabChange != NULL) free(PinsTabChange);
	
	PinsTabChange = New_ptr;
	PinsTabSize = 1;
	PinsTabStack = 0;
}

//**********************************************
//
// Odejmij element
//
//**********************************************

struct PinState periphPULL(void)
{
	if(PinsTabStack == 0)
	{
		printf("Periph Stack Error in PULL\n");
		exit(-1);
	}
	PinsTabStack--;
	return PinsTabChange[PinsTabStack];
}
//**********************************************
//
// Pobierz stempel czasowy najwyższej struktury na stosie
//
//**********************************************
CounterType getFirstElementTime(void){
	if(PinsTabStack == 0)
	{	
		//printf("FirstElementTime: No more elements\n");
		return 0;
	}
	return PinsTabChange[PinsTabStack-1].change_time;
}

//**********************************************
//
// Pusty Stos
//
//**********************************************
int periphIsStackEmpty(void){
	if(PinsTabStack == 0) return 1;
	else return 0;
}

//**********************************************
//
// Dodaj nowy element
//
//**********************************************

void periphPUSH(struct PinState state)
{
	PinsTabChange[PinsTabStack] = state;
	// Gdy tablica za mala
	if(PinsTabStack == (PinsTabSize-1)){ 
			PinsTabSize = 2*PinsTabSize;
			PinsTabChange = (struct PinState*)realloc(PinsTabChange, PinsTabSize*( sizeof(struct PinState)) );
			
			if(PinsTabChange == NULL){
				printf("Stack ERROR in PUSH\n");
				exit(-1);
			}
		}
	PinsTabStack++;
}

//**********************************************
//
// Sortowanie wg czasu najstarsze na dole
//
//**********************************************
void periphStackTimeSort(void){
	qsort(PinsTabChange, (size_t)(PinsTabStack), sizeof(struct PinState), time_compare);
}

int time_compare( const void * el_1, const void * el_2)
{
	const struct PinState* elem1 = (const struct PinState*) el_1;
	const struct PinState* elem2 = (const struct PinState*) el_2;
	
	if(elem1->change_time > elem2->change_time) return -1;
		else if(elem1->change_time < elem2->change_time) return 1;
		else if(elem1->change_time == elem2->change_time) return 0;
}



//**********************************************
//
// Laduj dane z pliku
//
//**********************************************

void loadPeriph(char *filename){
	printf("Read periph file %s\n",filename);
	// Otworz plik
	FILE *file_ptr = fopen(filename, "r");
	if(file_ptr == NULL) loadPeriph_ERROR("file no open");

	// Miejsce na stos periph
	periphNewPtr(malloc(sizeof(struct PinState)));
	int i;
	char line[MAX_LINE_SIZE];	
	// Pobieranie lini
	while(1){
			fgets(line, MAX_LINE_SIZE-1, file_ptr);	
			if( ferror(file_ptr)||feof(file_ptr) )break;

			i=0;
			while(line[i] != '\n') i++;
			line[i] = '\0';
		
			// Wepchnij strukture na stos
			periphPUSH(strtoPinStruct(line));
		}
	fclose(file_ptr);
	// Sortuj stos wg czasu
	periphStackTimeSort();
}

//**********************************************
//
// String na strukture 
//
//**********************************************

struct PinState strtoPinStruct(char* line){
	struct PinState temp_val;
	char *temp_str_ptr;
	// Ladowanie czasu	
	if((temp_str_ptr = strtok(line,":, ")) != NULL)
		temp_val.change_time = atoi(temp_str_ptr);
	else 
		loadPeriph_ERROR("format error -> time");
			
	// Ladowanie nr pinu
	if((temp_str_ptr = strtok(NULL,":, ")) != NULL)
		temp_val.pin_number = atoi(temp_str_ptr);
	else 
		loadPeriph_ERROR("format error -> pinNr");
			
	// Ladowanie wartosci
	if((temp_str_ptr = strtok(NULL,":, ")) != NULL)
		temp_val.pin_val = atof(temp_str_ptr);
	else 
		loadPeriph_ERROR("format error -> pinVal");	
	
	return temp_val;
}
 
//**********************************************
//
// Wyswietl stos
//
//**********************************************

 void printfPeriphTab(void){	
	int i = 0;
	for(i = 0; PinsTabStack != i ;i++)
	 {	 
	printf("%d-> %d: %d, %f\n",i,  PinsTabChange[i].change_time  ,  PinsTabChange[i].pin_number  ,  PinsTabChange[i].pin_val  ); 		 
	 }
 }
 
//**********************************************
//
// Blad odczytu
//
//**********************************************

void loadPeriph_ERROR(char* info){
	printf("Periph File ERROR: %s\n",info);
	periphFree();
	exit(-1);
}
 
//**********************************************
//
// Symulacja działania modułów sprzętowych procesora 
//
//**********************************************

void do_periph(const CounterType time){
	struct PinState pin_ch;

	// **** Aktualizacja wartości na pinach ****
	if(periphIsStackEmpty() == 0)// Gdy stos niepusty
	{
		// Pobieranie nowych stanów na pinach
		while(time == getFirstElementTime())
		{
			pin_ch = periphPULL();
			PinsCurrentVal[pin_ch.pin_number] = pin_ch.pin_val;
		}
	}
	
	// **** Działanie sprzętu ****
	do_AnalogComparator();		

	
	}

//******************************************
//
// Symulacja działanie Analog Comparatora
//
//******************************************
void do_AnalogComparator(void){0;}



