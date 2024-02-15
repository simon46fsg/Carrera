/*****************************************************************************/

/// \file       variable.h
/// \author     Frank Redlich
/// \version    1.01
/// \date       12.11.2017
/// \brief      Globale Variable
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/

/*
 neu an 1.01
 * Programmierblink Counter entfernt
 * Notaus Timer entfernt
 * Bremswirkung und v_max jetzt lokale Variable 
 */


#ifndef VARIABLE_H
#define VARIABLE_H

#include "defines.h"
#include "typedef.h"


extern struct CU_Daten_Struktur          CU_Daten;              // letztes empfangenes Datenwort
extern struct CU_Prg_Daten_Struktur      CU_Prg_Daten;          // letztes empfangenes Programmier-Datenwort
extern struct Spurwechseltaste_Struktur  Spurwechseltaste;      // Spurwechseltase für alle 6 Regler



extern  U8      eigene_Adresse,                                 // eigene Auto Adresse
                v_Ghostcar,                                     // einprogrammierte Ghostcar Geschwindigkeit 
                Programmiermodus,                               // wird das Auto gerade programmiert ?
                Ghostcar_Programmiermodus,                      // wird das Ghostcar gerade programmiert ?  
                v_Ghostcar,                                     // einprogrammierte Geschwindigkeit des Ghostcars
                Licht,                                          // Licht ein oder aus
         
                //Motor_PWM_Wert,                                 // aktuell verwendeter Wert der Motor PWM 
        
                Timer_Counter,                                  // allgemeiner Timer (alle 7,5 msec)
                Bitcounter,                                     // Bitzähler für CU Daten Empfang
                Bitmitte,                                       // zuletzt erfolgte eine Flanke in Bitmitte
                Telegramm_empfangen,                            // ein vollständiges Telegramm von der CU empfangen
                Telegrammtyp,                                   // Reglerdatenwort, Programmierdatenwort, Aktivdatenwort
                Letzter_Zustand_Licht_Taste,                    // letzter Zustand Spurwechseltaste
                Licht_Sperr_Timer,                              // Licht nur schalten, wenn der Motor schon kurze Zeit aus
                Adr_Programmier_timeout,                        // 2 Sekunden Timout für Programmiermodus
                Adr_warte_auf_Reset_timeout,                    // 2 Sekunden warten auf Reset, wenn nicht dann Prog EEPROM Byte rücksetzen
                Ghostcar_Doppelklick_timeout,                   // 2 s Zeitfnester nach Adressprogrammierung
                Ghostcar_Doppelklick_Counter,                   // wenn 2 dann in den Ghostcar Geschwindigkeit einstellen Mode
                Tank_leer,                                      // Tank Bit von CU
                Bremslicht_timer,                               // Länge des Einschalten des Bremslicht
                Letzter_Zustand_Bremse,                         // War die Bremse zuletzt ein oder aus
                DataBit[MAX_DATABITS],                          // Datenbits von CU
                Tank_leer_Blinken;                              // Blinken wegen Tankanzeige
        


extern S16      Alter_Timer_Wert;                               // alter Timer 1 Wert für Ermittlung Pulslänge





#endif // VARIABLE_H 
