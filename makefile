#USTAWIENIA KOMPILATORA

CC=gcc
CFLAGS=  -lm -c

# STRUKTURA PROJEKTU
INC_DIR = ./include
SRC_DIR = ./src
CMD_DIR = ./src/proc_commands


INC = -I$(INC_DIR)

# LISTA PLIKOW ZAWIERAJACYCH DEFINICJE INSTRUKCJE PROCESORA
# !!! MILO JAK LISTA BEDZIE AKTUALNA WSZYSTKO Z ROZSZEZENIEM *.o \
# 		 OCZYWISCIE W *.c PLIKI ZRODLOWE  !!!

CMD_OBJ = f_add1.o 	f_add2.o \
		   f_jmp_memc.o f_jmp_rel.o

# CELE

syko_procesor: main.o interpreter.o interrupt.o mem_abs.o $(CMD_OBJ)
	@echo Linkowanie syko_procesor:
	$(CC) $^ -o $@ 

%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) $(INC) $^ -o $@

%.o: $(CMD_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) $^ -o $@
	
.PHONY: clean
	
clean:
	rm -f *.o
	

