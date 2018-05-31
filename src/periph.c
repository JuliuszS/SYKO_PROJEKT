#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "types.h"
#include "periph.h"

#define MAX_LINE_SIZE 30 
#define SEPARATOR ','

/*
	!!! 
	Zmiany stanow pinow sa przechowywane wg
    czasowego ich wystepowania, na stosie w 
	postaci struktur zawierajacych czas pin 
	oraz wartość zmiany
*/

//**********************************************
//
// DEKLARACJA STOSU 
//
//**********************************************

struct PinState * PinsTab = NULL;
int PinsTabStack;
int PinsTabSize;

//**********************************************
//
// Zwolnij wskaznik na stos
//
//**********************************************

void periphFree(void)
{
	if(PinsTab != NULL) free(PinsTab);
	PinsTab = NULL;
}

//**********************************************
//
// Nowy wskaznik na stos
//
//**********************************************

void periphNewPtr(struct PinState* New_ptr)
{
	if(PinsTab != NULL) free(PinsTab);
	
	PinsTab = New_ptr;
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
		printf("Periph Stack Error\n");
		exit(-1);
	}
	PinsTabStack--;
	return PinsTab[PinsTabStack];
}

//**********************************************
//
// Dodaj nowy element
//
//**********************************************

void periphPUSH(struct PinState state)
{
	PinsTab[PinsTabStack] = state;
	// Gdy tablica za mala
	if(PinsTabStack == (PinsTabSize-1)){ 
			PinsTabSize = 2*PinsTabSize;
			PinsTab = (struct PinState*)realloc(PinsTab, PinsTabSize*( sizeof(struct PinState)) );
			
			if(PinsTab == NULL){
				printf("Stack ERROR\n");
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
	qsort(PinsTab, (size_t)(PinsTabStack+1), sizeof(struct PinState), time_compare);
}

int time_compare( const void * el_1, const void * el_2)
{
	const struct PinState* elem1 = (const struct PinState*) el_1;
	const struct PinState* elem2 = (const struct PinState*) el_2;
	
	if(elem1->change_time < elem2->change_time) return -1;
		else if(elem1->change_time > elem2->change_time) return 1;
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
	printf("%d-> %d: %d, %f\n",i,  PinsTab[i].change_time  ,  PinsTab[i].pin_number  ,  PinsTab[i].pin_val  ); 		 
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
// String na strukture 
//
//**********************************************

/*
void do_periph(void){
	
	
	
}
*/