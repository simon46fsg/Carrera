/*****************************************************************************/

/// \file       typedef.h
/// \author     Frank Redlich
/// \version    1.00
/// \date       28.03.2016
/// \brief      Definitionen von Typen (für 8 Bit-Prozessor) und Strukturen
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/


#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "defines.h"


typedef unsigned char 			U8;				// Unigned 8-bit number		0 ... 255 
typedef signed char 			S8;				// Signed 8-bit number		-128 ... 127 

typedef	unsigned int    		U16;			// Unsigned 16-bit number	0 ... 65535
typedef	signed int      		S16;			// Signed 16-bit number		-32768 ... 32767

//typedef	unsigned short long		U24;			// Unsigned 24-bit number	0 ... 2^24 - 1
//typedef	signed short long		S24;			// Signed 24-bit number		-2^23 ... 2^23 -1

typedef	unsigned long			U32;			// Unsigned 32-bit number	0 ... 2^32 - 1
typedef	signed long             S32;			// Signed 32-bit number		-2^31 ... 2^31 -1

typedef float                   F24;			// Float 24 Bit
typedef double                  F32;			// Float 32 Bit




struct EE_read_result{
    U8  Databyte;
    U8  Status;
};


struct CU_Daten_Struktur{
    U8  Adresse;
    U8  Spurwechseltaste;
    U8  Reglerwert;
    U8  Tankanzeige;
    U8  KFR;
    U8  FR;
};

struct CU_Prg_Daten_Struktur{
    U8  Adresse;
    U8  Wert;
    U8  Parameter;
    U8  Wert_alt;
    U8  Parameter_alt;
};


struct Spurwechseltaste_Struktur{
    U8  Counter[MAX_REGLER];
    U8  Letzter_Zustand[MAX_REGLER];
    U8  Reset_Timer[MAX_REGLER];
};


struct Timer_Reg_Struktur{
    U8  LSB;
    U8  MSB;
};

union Timer_Union{
    struct Timer_Reg_Struktur   Byte;
    S16                         Wort;
};
       
#endif // TYPEDEF_H 
