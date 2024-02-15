/*****************************************************************************/

/// \file       variable.c
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


#include "typedef.h"


#include "variable.h"

struct CU_Daten_Struktur            CU_Daten;                   ///> letztes empfangenes Datenwort
struct CU_Prg_Daten_Struktur        CU_Prg_Daten;               ///> letztes empfangenes Programmier-Datenwort
struct Spurwechseltaste_Struktur    Spurwechseltaste;           ///> Spurwechseltase für alle 6 Regler

U8              eigene_Adresse,                                 ///> eigene Auto Adresse                                   (EE_ADR_AUTO_ADRESSE)
                v_Ghostcar,                                     ///> einprogrammierte Ghostcar Geschwindigkeit             (EE_ADR_GHOST_GESCHWINDIGKEIT)
                Programmiermodus,                               ///> wird das Auto gerade programmiert ?                   (EE_ADR_PROGRAMMIERMODUS)
                Ghostcar_Programmiermodus,                      ///> wird gerade die Ghostcargeschwindigkeit programmiert? (EE_ADR_GHOST_PROGRAMMIERMODUS)
                v_Ghostcar,                                     ///> einprogrammierte Geschwindigkeit des Ghostcars        (EE_ADR_GHOST_GESCHWINDIGKEIT)
                Licht,                                          ///> Licht ein oder aus                                    (EE_ADR_LICHT)
        
                //Motor_PWM_Wert,                                 ///> aktuell verwendeter Wert der Motor PWM 
        
                Timer_Counter,                                  ///> allgemeiner Timer (alle 7,5 msec)
                Bitcounter,                                     ///> Bitzähler für CU Daten Empfang
                Bitmitte,                                       ///> zuletzt erfolgte eine Flanke in Bitmitte
                Telegramm_empfangen,                            ///> ein vollständiges Telegramm von der CU empfangen
                Telegrammtyp,                                   ///> Reglerdatenwort, Programmierdatenwort, Aktivdatenwort
                Letzter_Zustand_Licht_Taste,                    ///> letzter Zustand Spurwechseltaste
                Licht_Sperr_Timer,                              ///> Licht nur schalten, wenn der Motor schon kurze Zeit aus
                Adr_Programmier_timeout,                        ///> 2 Sekunden Timout für Programmiermodus
                Adr_warte_auf_Reset_timeout,                    ///> 2 Sekunden warten auf Reset, wenn nicht dann Prog EEPROM Byte rücksetzen
                Ghostcar_Doppelklick_timeout,                   ///> 3 s Zeitfnester nach Adressprogrammierung
                Ghostcar_Doppelklick_Counter,                   ///> wenn 2 dann in den Ghostcar Geschwindigkeit einstellen Mode
                Tank_leer,                                      ///> Tank Bit von CU
                Bremslicht_timer,                               ///> Länge des Einschalten des Bremslicht
                Letzter_Zustand_Bremse,                         ///> War die Bremse zuletzt ein oder aus
                DataBit[MAX_DATABITS],                          ///> Datenbits von CU
                Tank_leer_Blinken;                              ///> Blinken wegen Tankanzeige
                

S16             Alter_Timer_Wert;                               ///> alter Timer 1 Wert für Ermittlung Pulslänge
                



