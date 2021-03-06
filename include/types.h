#ifndef __TYPES_H__
#define __TYPES_H__

//definicje nowych typow danych
typedef unsigned char               DataType;
typedef unsigned short              CodeType;
typedef unsigned short              AddressType;
typedef unsigned long               CounterType;

//*****************************************************
//
// Informacje o zmianie stanu na pinie
//
//*****************************************************

struct PinState{
	int pin_number;
	float pin_val;
	CounterType change_time;
};

//*****************************************************
//
// unie do konwersji bit_bit zmiennych sign i usign
//
//*****************************************************

union bits{
	unsigned char unsign;
	signed char sign;
};
union word_bits{
	unsigned short unsign;
	signed short sign;
};

//*****************************************************
//najwieksze wartosci danych i adresów
#define MAX_ADDRESS                 0xFFFF
#define MAX_DATA_VAL                0xFF

//Numer ostatniego rejestru
#define REGISTERS_COUNT             (0x001F-0x0000)+1
#define MAX_REGISTER                REGISTERS_COUNT-1
#define IO_REGISTERS_COUNT          (0x005F-0x0020)+1
#define MAX_IO_REGISTERS            IO_REGISTERS_COUNT-1
#define EIO_REGISTERS_COUNT         (0x00FF-0x0060)+1
#define MAX_EIO_REGISTERS           EIO_REGISTERS_COUNT-1
 
#endif //__TYPES_H__