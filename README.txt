@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Wersja do testów, do sprawozdania. Zaimplementowane zosta³y wszystkie instrukcje z tresci zadania oraz dodatkowe (lista poni¿ej), powinny dzia³aæ poprawnie.

Zaimplementowane instrukcje:
ADD, JMP, RJMP, NOP, MOV, EOR, LDI, OUT, ICALL, MUL, NEG, ASR, RCALL

Do zaimplementowania zosta³ tylko komparator.


#################### TRESC ZADANIA ###########################
SYMULACJA PROCESORA AVR328p Projekt SYKO 2018 Lato

Zadanie:
Na bazie procesora Atmega328p utworzyæ wirtualny procesor,
emuluj¹cy dzia³anie analogowego komparatora. Dane o napiêciu
 maj¹ byæ czerpane z pliku flie_gpio_in.txt zawieraj¹cego stan
 napiêcia i stemple czasowe kiedy dane napiêcie mia³o siê
 pojawiæ na wejœciach komparatora. Emujacja wybranych instrukcji: 
 LPM, ICALL, RCALL, MUL, NEG, EOR, ASR.

Wymagane meta-testy: badanie poprawnoœci dzia³ania komparatora
 napiêæ analogowych wbudowanego w Atmega328p, badanie flagi "ACI"
 w trybie poolingu, badanie generacji przerwania "Analog Comparator",
 badanie poprawniœci dzia³ania: LPM, MUL, NEG, EOR, ASR.

Dodatkowe informacje na stronie przedmiotu
##############################################################

!!! Procesory AVR maja pamiêæ little endian, ale tylko 16-bitowa 
pamiêæ programu wymaga uwagi. 8-bitowa pamiêæ danych tego nie 
wymaga gdy¿ pojêcia little i big endian dotyczy tylko BAJTOW A 
NIE BITOW!!! ----->>>> Funkcje pobieraj¹ce pamiêæ programu, maj¹ 
zaimplementowan¹ konwersje na big endian co jest zgodne z modelem 
pamiêci w jezyku C dlatego martwiæ trzeba siê przy grzebaniu w 
funkcjach pamiêci programu, wiêc takie przypadki OBOWIAZKOWO 
oznaczamy.