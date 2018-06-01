#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "types.h"
#include "mem_abs.h"
#include "interpreter.h"
#include "interrupt.h"
#include "periph.h"

#define FILE_COUNTER            "test/file_counter.bin"
#define FILE_PC                 "test/file_pc.bin"
#define FILE_DATA               "test/file_data.bin"
#define FILE_CODE               "test/file_code.bin"
#define FILE_PERIPH 			"test/file_periph.txt"


int main(int argc, char *argv[]) {
    long counter=0, max_counter=0;      //liczba wykonanych instrukcji i zadana liczba instrukcji do wykonania
    long int_gen=-1;
    CodeType T;                         //zmienna pomocnicza - ma przechowywa� opcode instrukcji

	
//**************************************************
// Pomocnicze instrukcje resetuj�ce pliki PC i COUNTER
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
			 printf("do_SIM : Licznik cykli zosta� wyzerowany\n");
			 exit(0);
			}
	}
//**************************************************
// �adowanie Pami�ci
    loadMEMC(FILE_CODE);                //�adowanie pami�ci kodu z pliku
    loadMEMD(FILE_DATA);                //�adowanie pami�ci danych z pliku (w tym rejestr�wm)
    loadPC(FILE_PC);                    //�adowanie warto�ci PC
    loadCounter(FILE_COUNTER);          //�adowanie licznika cykli
	loadPeriph(FILE_PERIPH);			//�adowanie warto�ci napi�cia na pinach
	/*
	printf("--------- Periph TAB -------------\n");
	printfPeriphTab();
	printf("--------- Periph END -------------\n");
    */
	dumpMEMConfiguration();

	
//**************************************************
// Argumenty wywo�anie symulacji  
	if(argc>1)
		{	                        //pierwszy parametr wywolania okresla liczbe instrukcji do wykonania
		 max_counter=strtoul(argv[1], NULL, 10);
		 max_counter+=getCounter();
		}
	if(max_counter==0)
		{	
		 max_counter=getCounter()+1;     //nie podanie argumentu wywolania lub b�edne jego podanie - ustala wykonanie jednego cyklu
		}
    if(argc>2)
		{ 
		//drugi parametr wywolania okresla liczbe instrukcji po ktorych ma byc wygenerowane przerwanie
		 int_gen=strtoul(argv[2], NULL, 10);
		}
    if(int_gen==0)
		{
		 int_gen=-1;                     //nie podanie argumentu wywolania lub b�edne jego podanie - ustala wykonanie jednej instrukcji
		}
    if(int_gen>0)
		 set_intterrupt(int_gen);        //zapamietaj kiedy wywolac przerwanie
	 
//**************************************************
// Rozpocz�cie pracy	
	printf("---------------------- START ----------------------------\r\n");
    for(;;)
	{
		do_periph(getCounter()); // Dzia�anie modu��w sprz�towych 
		T=getOpcode();                  //T=opcode operacji (w��cznie z arg. wbudowanym)
		doInstr(T);                     //wykonaj instrukcje
		checkInterrupt(getCounter());   //sprawd� czy trzeba wygenerowac przerwanie

		if(getCounter()>=max_counter)  // czy wykonano zadan� liczb� cykli
		{  
			saveCPUState();
			periphFree();	
			printf("Nacisnij ENTER by zakonczyc: return 0\n");
			getchar();
			return 0;
		}
	}
	
    printf("Bledne wykonanie emulacji (PC=0x%08lx, T=0x%08lx)\r\n", getPC(), T);
	printf("Nacisnij ENTER by zakonczyc\n");
	getchar();
    saveCPUState();                     //!!! - Tu niepowinnismy si� nigdy znale��
    return -2;
}

