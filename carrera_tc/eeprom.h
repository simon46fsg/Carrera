/*****************************************************************************/

/// \file       EEPROM.h
/// \author     Frank Redlich
/// \version    1.00
/// \date       31.01.2016
/// \brief      Prototypen für Zugriff auf das interne EEPROM
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/


#ifndef EEPROM_H
#define	EEPROM_H


#define   EE_ADR_AUTO_ADRESSE           0x01
#define   EE_ADR_LICHT                  0x02
#define   EE_ADR_PROGRAMMIERMODUS       0x03
#define   EE_ADR_BREMSWIRKUNG           0x04
#define   EE_ADR_MAX_GESCHWINDIGKEIT    0x05
//#define   EE_ADR_GHOST_CAR_MODE         0x06
#define   EE_ADR_GHOST_GESCHWINDIGKEIT  0x07
#define   EE_ADR_GHOST_PROGRAMMIERMODUS 0x08

#define   EE_ADR_DEFAULT_0XAA           0x10
#define   EE_ADR_DEFAULT_0X55           0x11




U8 EE_read (U8 Adresse);

void EE_write (U8 Databyte, U8 Adresse);
U8 EE_write_verified (U8 Databyte, U8 Adresse);



#endif	/* EEPROM_H */

