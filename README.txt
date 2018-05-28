@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Wersja do test�w, do sprawozdania. Zaimplementowane zosta�y wszystkie instrukcje z tresci zadania oraz dodatkowe (lista poni�ej), powinny dzia�a� poprawnie.

Zaimplementowane instrukcje:
ADD, JMP, RJMP, NOP, MOV, EOR, LDI, OUT, ICALL, MUL, NEG, ASR, RCALL

Do zaimplementowania zosta� tylko komparator.


#################### TRESC ZADANIA ###########################
SYMULACJA PROCESORA AVR328p Projekt SYKO 2018 Lato

Zadanie:
Na bazie procesora Atmega328p utworzy� wirtualny procesor,
emuluj�cy dzia�anie analogowego komparatora. Dane o napi�ciu
 maj� by� czerpane z pliku flie_gpio_in.txt zawieraj�cego stan
 napi�cia i stemple czasowe kiedy dane napi�cie mia�o si�
 pojawi� na wej�ciach komparatora. Emujacja wybranych instrukcji: 
 LPM, ICALL, RCALL, MUL, NEG, EOR, ASR.

Wymagane meta-testy: badanie poprawno�ci dzia�ania komparatora
 napi�� analogowych wbudowanego w Atmega328p, badanie flagi "ACI"
 w trybie poolingu, badanie generacji przerwania "Analog Comparator",
 badanie poprawni�ci dzia�ania: LPM, MUL, NEG, EOR, ASR.

Dodatkowe informacje na stronie przedmiotu
##############################################################

!!! Procesory AVR maja pami�� little endian, ale tylko 16-bitowa 
pami�� programu wymaga uwagi. 8-bitowa pami�� danych tego nie 
wymaga gdy� poj�cia little i big endian dotyczy tylko BAJTOW A 
NIE BITOW!!! ----->>>> Funkcje pobieraj�ce pami�� programu, maj� 
zaimplementowan� konwersje na big endian co jest zgodne z modelem 
pami�ci w jezyku C dlatego martwi� trzeba si� przy grzebaniu w 
funkcjach pami�ci programu, wi�c takie przypadki OBOWIAZKOWO 
oznaczamy.