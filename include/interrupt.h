#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

// Sprawdź przerwanie
void checkInterrupt(void);

// Przerwanie Analog Comparator
int checkAC_Interrupt(void);

//**************************************
//
// Adresy wektorów przerwań
//
//**************************************

#define RESET_VECT 0x0000 // RESET External Pin, Power-on Reset, Brown-out Reset and Watchdog System Reset
/*
#define  0x0002 //INT0 External Interrupt Request 0
#define  0x0004 //INT1 External Interrupt Request 1
#define  0x0006 //PCINT0 Pin Change Interrupt Request 0
#define  0x0008 //PCINT1 //Pin Change Interrupt Request 1
#define  0x000A //PCINT2 Pin Change Interrupt Request 2
#define  0x000C //WDT Watchdog Time-out Interrupt
#define  0x000E //TIMER2_COMPA Timer/Counter2 Compare Match A
#define  0x0010 //TIMER2_COMPB Timer/Coutner2 Compare Match B
#define  0x0012 //TIMER2_OVF Timer/Counter2 Overflow
#define  0x0014 //TIMER1_CAPT Timer/Counter1 Capture Event
#define  0x0016 //TIMER1_COMPA Timer/Counter1 Compare Match A
#define  0x0018 //TIMER1_COMPB Timer/Coutner1 Compare Match B
#define  0x001A //TIMER1_OVF Timer/Counter1 Overflow
#define  0x001C //TIMER0_COMPA Timer/Counter0 Compare Match A
#define  0x001E //TIMER0_COMPB Timer/Coutner0 Compare Match B
#define  0x0020 //TIMER0_OVF Timer/Counter0 Overflow
#define  0x0022 //SPI STC SPI Serial Transfer Complete
#define  0x0024 //USART_RX USART Rx Complete
#define  0x0026 //USART_UDRE USART Data Register Empty
#define  0x0028 //USART_TX USART Tx Complete
#define  0x002A //ADC ADC Conversion Complete
#define  0x002C //EE READY EEPROM Ready
*/
#define AC_VECTOR  0x002E //ANALOG COMP Analog Comparator

//**************************************

#endif //__INTERRUPTS_H__
