/*****************************************************************************/

/// \file       init.h
/// \author     Frank Redlich
/// \version    1.01
/// \date       30.12.2017
/// \brief      Definitionen der Initialisierungsroutinen
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   standard oder DIY

/******************************************************************************/
/*
 neu an 1.01 
 * init CCP4 f�r PWM R�cklicht/Bremslicht f�r DIY Decoder
 */


#ifndef INIT_H
#define INIT_H

#include "typedef.h"


//--------------------------------------------------------- interne Funktionen

void Initialisierung(void);

void alle_Variablen_ruecksetzen(void);

//void Init_Timer_0(void);          // Timer mit Overflow Interrupt 16,384 ms
void Init_Timer_1(void);          // Zeitbasis f�r Pulsweitenmessung der CU Daten
void Init_Timer_4(void);          // Takt f�r CCP1 und CCP2
void Init_CCP1(void);             // Motorsteuerung
void Init_CCP2(void);             // Bremse
void Init_CCP3(U8 Periodendauer); // IR LED
void Init_CCP4(void);             // PWM f�r Bremslicht/R�cklicht 

void Init_Timer_6(void);          // f�r Timeout beim Datenempfang
void Init_IOC_Interrupt(void);    // Portpin Interrupts 

void Init_EEPROM_Defaultwerte(void);



#endif // INIT_H
