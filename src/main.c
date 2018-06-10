#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "types.h"
#include "mem_abs.h"
#include "interpreter.h"
#include "interrupt.h"
#include "periph.h"



int main(int argc, char *argv[]) {
    long counter=0, max_counter=0;      //liczba wykonanych instrukcji i zadana liczba instrukcji do wykonania
    long int_gen=-1;
    CodeType T;                         //zmienna pomocnicza - ma przechowywaæ opcode instrukcji

//**************************************************
// Pomocnicze instrukcje resetuj¹ce pliki PC i COUNTER
	if(argc>1){
		if(strcmp(argv[1],"SIM=0") == 0)
			{
			 setPC(0);
			 savePC(FILE_PC);
			 printf("do_SIM : PC zostal wyzerowany\n");
			 
			 setCounter(0);
			 saveCounter(FILE_COUNTER);	
			 printf("do_SIM : Licznik cykli zostal wyzerowany\n");
			 
			 exit(0);
			}
		if(strcmp(argv[1],"PC=0") == 0)
			{
			 setPC(0);
			 savePC(FILE_PC);
			 printf("do_SIM : PC zostal wyzerowany\n");
			 exit(0);
			}
		if(strcmp(argv[1],"COUNTER=0") == 0)
			{
			 setCounter(0);
			 saveCounter(FILE_COUNTER);	
			 printf("do_SIM : Licznik cykli zosta³ wyzerowany\n");
			 exit(0);
			}
	}
//**************************************************
// £adowanie Pamiêci
    loadMEMC(FILE_CODE);                //£adowanie pamiêci kodu z pliku
    loadMEMD(FILE_DATA);                //£adowanie pamiêci danych z pliku (w tym rejestrówm)
    loadPC(FILE_PC);                    //£adowanie wartoœci PC
    loadCounter(FILE_COUNTER);          //£adowanie licznika cykli
	loadFlagsRegister(FILE_FLAGS);		//£adowanie rejestru flag
	loadPeriph(FILE_PERIPH);			//£adowanie wartoœci napiêcia na pinach
	loadPeriphCurrent(FILE_PERIPH_CURRENT);
	
	
	dumpMEMConfiguration();
	/*
	printf("--------- Periph TAB -------------\n");
	printfPeriphTab();
	printfPinsCurrentValTab();
	printf("--------- Periph END -------------\n");
   */
 	
//**************************************************
// Argumenty wywo³anie symulacji  
	if(argc>1)
		{	                        //pierwszy parametr wywolania okresla liczbe instrukcji do wykonania
		 max_counter=strtoul(argv[1], NULL, 10);
		 max_counter+=getCounter();
		}
	if(max_counter==0)
		{	
		 max_counter=getCounter()+1;     //nie podanie argumentu wywolania lub b³edne jego podanie - ustala wykonanie jednego cyklu
		}

	 
//**************************************************
// Rozpoczêcie pracy	
	printf("\n--- START ---\r\n");
    for(;;)
	{
		do_periph(getCounter()); // Dzia³anie modu³ów sprzêtowych 
		T=getOpcode();                  //T=opcode operacji (w³¹cznie z arg. wbudowanym)
		doInstr(T);                     //wykonaj instrukcje
		checkInterrupt();   //sprawdŸ czy trzeba wygenerowac przerwanie
		
		if(getCounter()>=max_counter)  // czy wykonano zadan¹ liczbê cykli
		{  
			printf("---  END  ---\r\n");
			saveCPUState();
			savePeriphCurrent(FILE_PERIPH_CURRENT); // zapisz stan pinow
			periphFree();	
			printf("Nacisnij ENTER by zakonczyc: return 0\n");
			getchar();
			return 0;
		}
	}
	
    printf("Bledne wykonanie emulacji (PC=0x%08lx, T=0x%08lx)\r\n", getPC(), T);
	printf("Nacisnij ENTER by zakonczyc\n");
	getchar();
	savePeriphCurrent(FILE_PERIPH_CURRENT); // zapisz stan pinow
    saveCPUState();                     //!!! - Tu niepowinnismy siê nigdy znaleŸæ
    return -2;
}

