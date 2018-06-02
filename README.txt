@@@@@@@@@@@@@@@@@@@@ STAN PROJEKTU @@@@@@@@@@@@@@@@@@@@@@@

Wersja ko�cowa do sprawozdania. Zaimplementowane zosta�y wszystkie instrukcje z tre�ci zadania oraz dodatkowe (lista poni�ej), powinny dzia�a� poprawnie. Opr�cz tego zosta� zaimplementowany mechanizm odpowiedzialny za W danych do pin�w (wyj�cia nie zaimplementowano, poniewa� nie jest to wymagane, ale mo�na to do�� �atwo zrobi�). Na tej podstawie zaimplementowano Analog Comparator procesora. 

Zaimplementowane instrukcje: 
IN, STS, ADD, JMP, RJMP, NOP, MOV, EOR, LDI, OUT, ICALL, MUL, NEG, ASR, RCALL

@@@@@@@@@@@@@@@@@@@@@@@@ JAK U�YWA� ? @@@@@@@@@@@@@@@@@@@@@@@@

Do kompilacji wymagany zainstalowany kompilator "gcc" oraz narz�dzie "make"(dzia�a pod win10), mo�na u�ywa� innego kompilatora np. clang ale nale�y zmodyfikowa� linie CC=gcc w pliku makefile. Program kompiluje si� poleceniem "make" wywo�anym w folderze g��wnym SYKO_Procesor. Wynikiem kompilacji jest plik do_sim.(exe/out), podczas kompilacji mo�e wyst�pi� warning zwi�zany z przerwaniami, ale mo�na go zignorowa�. Poleceniem "make clean" mo�emy usun�� pliki .o powsta�e po kompilacji. Do przeprowadzenia symulacji potrzebne s� pliki zawieraj�ce takie dane jak kod programu obecn� zawarto�� pami�ci RAM itp. Wszystkie pliki powinny si� znajdowa� w folderze /test i mie� nast�puj�ce nazwy. 

file_counter.bin - licznik wykonanych instrukcji

file_code.bin - zawiera kod programu

file_data.bin - zawiera pocz�tkow� zawarto�� RAM

file_current_p.bin - pocz�tkowy stan pin�w procesora
 
file_pc.bin - pocz�tkowa warto�� licznika programu 

file_periph.txt - plik opisuj�cy zmiany warto�ci napi�cia na pinach procesora 

Jako �e pliki .bin przechowuj� dane w postaci binarnej do otworzenia plik�w potrzeba odpowiedniego programu. Osobi�cie u�ywam "HxD". 

"Procesor" programujemy przez zmian� pliku file_code.bin Mo�emy to zrobi� poprzez wpisywanie odpowiednich binarnych OPCod�w instrukcji lub co jest przyjemniejsze zainstalowanie jakiego� kompilatora assemblera dla AVRki. Pruszkowski poleca� �rodowisko zwi�zane z Arduino. Ja osobi�cie u�ywam Eclipsa z AVR plugin i gcc dla AVR. Program pisz� przez wstawki asemblerowe. Po kompilacji programu otwieram plik .lss zawieraj�cy instrukcje i ich op cody w hexie kt�re wklejam do file_code.bin Trzeba niestety uwa�a�, poniewa� w obr�bie s�owa bajty m�odsze w s� zamienione ze starszymi "BIGENDIAN" co trzeba skorygowa� r�cznie. Jak zainstalowa� eclipse z avr plugin znajdziecie na youtube na kanale  "mirekk36" od razu powiem, �e instalacja zajmuje du�o czasu a ja skorzysta�em z tej metody, poniewa� wcze�niej programowa�em AVRki i mia�em to wszystko zainstalowane. Program do_sim dzia�a w nast�puj�cy spos�b. 

1. Najpierw program �aduje wszystkie dane: pami�� procesora itp. 
2. Jako argument wywo�ania przyjmuje liczb�instrukcji, kt�re chcemy wywo�a� w trakcie symulacji 
3. Program wykonuje instrukcje 
4. Na koniec zapisuje do plik�w stan procesora. 

Przyk�adowe wywo�anie: do_sim3 -> "wykonaj 3 instrukcje"

Dzi�ki krokowi 4. Mo�emy podejrze� stan procesora po wykonaniu okre�lonej liczby instrukcji oraz wykorzysta� do ponownego wywo�ania do_sim i dalszej symulacji. Warto tu zaznaczy�, do czego s�u�y plik file_counter.bin oraz czym si� r�ni licznik wykonanych instrukcji od licznika programu. Licznik programu wskazuje na nast�pn� instrukcj� w pami�ci do wykonania, a wi�c PC to adres. Licznik wykonanych instrukcji pokazuje, ile instrukcji dotychczas wykona� procesor. Rzeczywisty procesor nie ma takiego licznika i istnieje on tylko na potrzeby symulacji. Celem tego licznika jest wskazywanie mechanizmom odpowiedzialnym za zmiany warto�ci na pinach, kiedy nale�y to zrobi�. W pewnym sensie implementuje on up�ywaj�cy czas. 

Plik file_periph.txt przechowuj� zmiany stan�w na pinach w nast�puj�cym formacie "czas_zmiany:pin,nowa_warto��" "czas_zmiany" oraz "pin" to int a "nowa_warto��" to float np. "20:5,3.4" -> (gdy counter 20 ustaw na pinie 5 warto�� 3.4)

Jako �e cz�sto zachodzi potrzeba wyzerowania plik�w zawieraj�cych PC oraz licznik wykonywanych instrukcji w celu u�atwienia pracy dodano nast�puj�ce polecenia. 

PC=0- zeruje file_pc.bin

COUNTER=0 - zeruje file_counter.bin

SIM=0 - zeruje file_pc.bin oraz file_counter.bin 

przyk�adowe wywo�anie "do_sim SIM=0"

#################### Tre�� ZADANIA ########################### SYMULACJA PROCESORA AVR328p Projekt SYKO 2018 Lato Zadanie: Na bazie procesora Atmega328p utworzy� wirtualny procesor, emuluj�cy dzia�anie analogowego komparatora. Dane o napi�ciu maj� by� czerpane z pliku flie_gpio_in.txt zawieraj�cego stan napi�cia i stemple czasowe, kiedy dane napi�cie mia�o si� pojawi� na wej�ciach komparatora. Emujacja wybranych instrukcji: LPM, ICALL, RCALL, MUL, NEG, EOR, ASR. 

Wymagane meta-testy: badanie poprawno�ci dzia�ania komparatora napi�� analogowych wbudowanego w Atmega328p, badanie flagi "ACI" w trybie poolingu, badanie generacji przerwania "AnalogComparator", badanie poprawno�ci dzia�ania: LPM, MUL, NEG, EOR, ASR. 

Dodatkowe informacje na stronie przedmiotu ############################################################## 