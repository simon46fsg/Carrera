/*****************************************************************************/

/// \file       EEPROM.c
/// \author     Frank Redlich
/// \version    1.00
/// \date       11.11.2017
/// \brief      Zugriff auf das interne EEPROM
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   decoder

/******************************************************************************/

/*
 neu an 1.01
 * kein Blinken mehr wenn irgendeine EEPROM Zelle beschrieben wird 
 * 
 */

//#include <xc.h> microchip specific stuff
#include "ports.h"
#include "init.h"
#include "typedef.h"
#include "defines.h"
#include "variable.h"

#include "eeprom.h"






/**
 * liest ein Byte aus dem internen EEPROM
 * 
 * @param Adresse   Adresse im EEPROM 0 ... 255
 * @return          ausgelesener Wert
 */
U8 EE_read (U8 Adresse)
{
    U8  Databyte;

//    EEADRL = Adresse;
//    EECON1bits.EEPGD = 0;   // point to DATA memory
//    EECON1bits.CFGS = 0;    // deselect config space
//    EECON1bits.RD = 1;      // EE read
//
//    Databyte = EEDATL;

    //replace with code for external eeprom or some other mean to save data or just fuck it and hard code it


    return (Databyte);
}

/******************************************************************************/

/**
 * Schreiben mit Verify eines Bytes im EEPROM
 *
 * @param Databyte      Daten Byte
 * @param Adresse       Adresse im EEPROM 0 ... 255
 * @return              OK wenn verify fehlerfrei, sonst NOK
 */
U8 EE_write_verified (U8 Databyte, U8 Adresse)
{
    U8      Ergebnis,
            Versuche,
            Testbyte;


    Versuche = 5;
    Ergebnis = NOK;
    while ((Versuche > 0) && (Ergebnis == NOK))
    {
         EE_write (Databyte, Adresse);
         Testbyte = EE_read (Adresse);
         if (Testbyte == Databyte)
             Ergebnis = OK;
         Versuche--;
    }
    
    
    return(Ergebnis);
}


/******************************************************************************/


/**
 * schreibt ein Byte in das interne EEPROM
 * ohne verify
 * 
 * @param Databyte      Daten Byte
 * @param Adresse       Adresse im EEPROM 0 ... 255
 */
void EE_write (U8 Databyte, U8 Adresse)
{

//    EEADRL = Adresse;
//    EEDATL = Databyte;
//    EECON1bits.CFGS = 0;        // deselect config space
//    EECON1bits.EEPGD = 0;       // point to DATA memory
//    EECON1bits.WREN = 1;        // EE write enable
//
//    INTCONbits.GIE = 0;         // Global interrupt disable
//    EECON2 = 0x55;
//    EECON2 = 0xAA;
//    EECON1bits.WR = 1;          // EE write
//    INTCONbits.GIE = 1;         // Global interrupt enable
//
//    EECON1bits.WREN = 0;        // EE write disable
//
//    while (EECON1bits.WR == 1)  // warten bis fertig
//    {
//        NOP();
//    }

	//replace with code for external eeprom
}

/******************************************************************************/

