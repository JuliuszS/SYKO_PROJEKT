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
// Pobierz napiecie na pinie
//
//**********************************************
float getPinVal(int pin_number){
	if( (pin_number > NUMBERS_OF_PINS) || (pin_number <= 0) )
	{
			printf("Error PinVal: pin_number = %d",pin_number);
			exit(-1);
	}
	return	PinsCurrentVal[pin_number-1];
}

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
// Laduj zmiany stanów  z pliku
//
//**********************************************

void loadPeriph(char *filename){
	printf("Read periph file %s\n",filename);
	// Otworz plik
	FILE *file_ptr = fopen(filename, "r");
	if(file_ptr == NULL) loadPeriph_ERROR("file no open\n");

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
// laduj obecny stan pinow
//
//**********************************************
void loadPeriphCurrent(char *file){       
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("Periph Current file not found (%s)!\n", file);
        exit(-4);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    printf("Read Periph (%s) file in %dbytes\n", file, read(file_ptr, (void*)PinsCurrentVal, sizeof(float)*(NUMBERS_OF_PINS+1)));
    close(file_ptr);
}

//**********************************************
//
// laduj stan pinow
//
//**********************************************
void savePeriphCurrent(char *file){        
    int file_ptr;
    file_ptr=open(file, O_RDWR | O_BINARY, 0);
    if(file_ptr<0){
        printf("Periph Current file cannot open to write (%s)!\n", file);
        exit(-6);
    }    
    lseek(file_ptr, 0, SEEK_SET);
    printf("Periph Current file (%s) in %dbytes\n", file, write(file_ptr, (void*)PinsCurrentVal, sizeof(float)*(NUMBERS_OF_PINS)));
    close(file_ptr);
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
	printf("StackPtrVal = %d\n",PinsTabStack);
	for(i = 0; PinsTabStack > i ;i++)
	 {	 
	printf("%d-> %d: %d, %f\n",i,  PinsTabChange[i].change_time  ,  PinsTabChange[i].pin_number  ,  PinsTabChange[i].pin_val  ); 		 
	 }
 }
 
 
 void printfPinsCurrentValTab(){	
	int i = 0;
	printf("PinsCurrentVal:\nPIN -> VAL\n");
	for(i = 0; NUMBERS_OF_PINS > i ;i++)
	 {	 
		printf("%d -> %f\n",i,PinsCurrentVal[i]); 		 
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
			if(periphIsStackEmpty()) break; // Gdy stos sie opróżnił
			pin_ch = periphPULL();
			PinsCurrentVal[(pin_ch.pin_number)-1] = pin_ch.pin_val;
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
void do_AnalogComparator(void){
	
	DataType ACSR = getIORegister(A_ACSR_ADDRESS);
	DataType ADCSRB = getMEMD(ADCSRB_ADDRESS);
	DataType ADCSRA = getMEMD(ADCSRA_ADDRESS);
	DataType DIDR1 = getMEMD(DIDR1_ADDRESS);
	
	float IN1, IN2;
	
	if((ACSR&ACD) == 0){// Czy moduł wyłączony?
		// IN 1
		if(ACSR&ACBG) IN1 = 0; // Bandgap voltage
		else IN1 = getPinVal(AIN0); // PIN AIN0
		// IN 2
		if(ADCSRB&ACME)
		{
			if(ADCSRA&ADEN) 
				IN2 = getPinVal(AIN1);
			else
			{
				DataType MUX = 0x07&getMEMD(ADMUX_ADDRESS);
				switch(MUX){
					case 0x00:
						IN2 = getPinVal(ADC0);
						break;
					case 0x01:
						IN2 = getPinVal(ADC1);
						break;
					case 0x02:
						IN2 = getPinVal(ADC2);
						break;
					case 0x03:
						IN2 = getPinVal(ADC3);
						break;
					case 0x04:
						IN2 = getPinVal(ADC4);
						break;
					case 0x05:
						IN2 = getPinVal(ADC5);
						break;
					case 0x06:
						IN2 = getPinVal(ADC6);
						break;
					case 0x07:
						IN2 = getPinVal(ADC7);
				}
			}
		}
		else IN2 = getPinVal(AIN1);
		// PINY IN1 i IN2 wybrane
		if(IN1>IN2){
				setIORegister(A_ACSR_ADDRESS,ACSR |=   ACO); // USTAW ACO
			}
		else    
			{
				setIORegister(A_ACSR_ADDRESS,ACSR &= ~(ACO)); // ZERUJ ACO
			}
		
	}else printf("	Modul nie dziala\n");
	
	
}



