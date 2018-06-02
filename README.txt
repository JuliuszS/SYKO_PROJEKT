@@@@@@@@@@@@@@@@@@@@ STAN PROJEKTU @@@@@@@@@@@@@@@@@@@@@@@

Wersja koñcowa do sprawozdania. Zaimplementowane zosta³y wszystkie instrukcje z treœci zadania oraz dodatkowe (lista poni¿ej), powinny dzia³aæ poprawnie. Oprócz tego zosta³ zaimplementowany mechanizm odpowiedzialny za W danych do pinów (wyjœcia nie zaimplementowano, poniewa¿ nie jest to wymagane, ale mo¿na to doœæ ³atwo zrobiæ). Na tej podstawie zaimplementowano Analog Comparator procesora. 

Zaimplementowane instrukcje: 
IN, STS, ADD, JMP, RJMP, NOP, MOV, EOR, LDI, OUT, ICALL, MUL, NEG, ASR, RCALL

@@@@@@@@@@@@@@@@@@@@@@@@ JAK U¯YWAÆ ? @@@@@@@@@@@@@@@@@@@@@@@@

Do kompilacji wymagany zainstalowany kompilator "gcc" oraz narzêdzie "make"(dzia³a pod win10), mo¿na u¿ywaæ innego kompilatora np. clang ale nale¿y zmodyfikowaæ linie CC=gcc w pliku makefile. Program kompiluje siê poleceniem "make" wywo³anym w folderze g³ównym SYKO_Procesor. Wynikiem kompilacji jest plik do_sim.(exe/out), podczas kompilacji mo¿e wyst¹piæ warning zwi¹zany z przerwaniami, ale mo¿na go zignorowaæ. Poleceniem "make clean" mo¿emy usun¹æ pliki .o powsta³e po kompilacji. Do przeprowadzenia symulacji potrzebne s¹ pliki zawieraj¹ce takie dane jak kod programu obecn¹ zawartoœæ pamiêci RAM itp. Wszystkie pliki powinny siê znajdowaæ w folderze /test i mieæ nastêpuj¹ce nazwy. 

file_counter.bin - licznik wykonanych instrukcji

file_code.bin - zawiera kod programu

file_data.bin - zawiera pocz¹tkow¹ zawartoœæ RAM

file_current_p.bin - pocz¹tkowy stan pinów procesora
 
file_pc.bin - pocz¹tkowa wartoœæ licznika programu 

file_periph.txt - plik opisuj¹cy zmiany wartoœci napiêcia na pinach procesora 

Jako ¿e pliki .bin przechowuj¹ dane w postaci binarnej do otworzenia plików potrzeba odpowiedniego programu. Osobiœcie u¿ywam "HxD". 

"Procesor" programujemy przez zmianê pliku file_code.bin Mo¿emy to zrobiæ poprzez wpisywanie odpowiednich binarnych OPCodów instrukcji lub co jest przyjemniejsze zainstalowanie jakiegoœ kompilatora assemblera dla AVRki. Pruszkowski poleca³ œrodowisko zwi¹zane z Arduino. Ja osobiœcie u¿ywam Eclipsa z AVR plugin i gcc dla AVR. Program piszê przez wstawki asemblerowe. Po kompilacji programu otwieram plik .lss zawieraj¹cy instrukcje i ich op cody w hexie które wklejam do file_code.bin Trzeba niestety uwa¿aæ, poniewa¿ w obrêbie s³owa bajty m³odsze w s¹ zamienione ze starszymi "BIGENDIAN" co trzeba skorygowaæ rêcznie. Jak zainstalowaæ eclipse z avr plugin znajdziecie na youtube na kanale  "mirekk36" od razu powiem, ¿e instalacja zajmuje du¿o czasu a ja skorzysta³em z tej metody, poniewa¿ wczeœniej programowa³em AVRki i mia³em to wszystko zainstalowane. Program do_sim dzia³a w nastêpuj¹cy sposób. 

1. Najpierw program ³aduje wszystkie dane: pamiêæ procesora itp. 
2. Jako argument wywo³ania przyjmuje liczbêinstrukcji, które chcemy wywo³aæ w trakcie symulacji 
3. Program wykonuje instrukcje 
4. Na koniec zapisuje do plików stan procesora. 

Przyk³adowe wywo³anie: do_sim3 -> "wykonaj 3 instrukcje"

Dziêki krokowi 4. Mo¿emy podejrzeæ stan procesora po wykonaniu okreœlonej liczby instrukcji oraz wykorzystaæ do ponownego wywo³ania do_sim i dalszej symulacji. Warto tu zaznaczyæ, do czego s³u¿y plik file_counter.bin oraz czym siê ró¿ni licznik wykonanych instrukcji od licznika programu. Licznik programu wskazuje na nastêpn¹ instrukcjê w pamiêci do wykonania, a wiêc PC to adres. Licznik wykonanych instrukcji pokazuje, ile instrukcji dotychczas wykona³ procesor. Rzeczywisty procesor nie ma takiego licznika i istnieje on tylko na potrzeby symulacji. Celem tego licznika jest wskazywanie mechanizmom odpowiedzialnym za zmiany wartoœci na pinach, kiedy nale¿y to zrobiæ. W pewnym sensie implementuje on up³ywaj¹cy czas. 

Plik file_periph.txt przechowujê zmiany stanów na pinach w nastêpuj¹cym formacie "czas_zmiany:pin,nowa_wartoœæ" "czas_zmiany" oraz "pin" to int a "nowa_wartoœæ" to float np. "20:5,3.4" -> (gdy counter 20 ustaw na pinie 5 wartoœæ 3.4)

Jako ¿e czêsto zachodzi potrzeba wyzerowania plików zawieraj¹cych PC oraz licznik wykonywanych instrukcji w celu u³atwienia pracy dodano nastêpuj¹ce polecenia. 

PC=0- zeruje file_pc.bin

COUNTER=0 - zeruje file_counter.bin

SIM=0 - zeruje file_pc.bin oraz file_counter.bin 

przyk³adowe wywo³anie "do_sim SIM=0"

#################### Treœæ ZADANIA ########################### SYMULACJA PROCESORA AVR328p Projekt SYKO 2018 Lato Zadanie: Na bazie procesora Atmega328p utworzyæ wirtualny procesor, emuluj¹cy dzia³anie analogowego komparatora. Dane o napiêciu maj¹ byæ czerpane z pliku flie_gpio_in.txt zawieraj¹cego stan napiêcia i stemple czasowe, kiedy dane napiêcie mia³o siê pojawiæ na wejœciach komparatora. Emujacja wybranych instrukcji: LPM, ICALL, RCALL, MUL, NEG, EOR, ASR. 

Wymagane meta-testy: badanie poprawnoœci dzia³ania komparatora napiêæ analogowych wbudowanego w Atmega328p, badanie flagi "ACI" w trybie poolingu, badanie generacji przerwania "AnalogComparator", badanie poprawnoœci dzia³ania: LPM, MUL, NEG, EOR, ASR. 

Dodatkowe informacje na stronie przedmiotu ############################################################## 