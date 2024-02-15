/*****************************************************************************/

/// \file       defines.h
/// \author     Frank Redlich
/// \version    1.05
/// \date       26.12.2020
/// \brief      allgemeine defines
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/
/*
 neu an 1.01 
 * getrennte Pulslängen für High und Low-Pulse. Durch das Schaltverhalten des
   Transistors ist die Highphase immer kürzer als die Low Phase 

 neu an 1.02 
 * verschiedene Defines für 16 MHz Takt und 32 MHz Takt  
  
 neu an 1.03
 * compilerswitch für Prozessortakt entfernt, jetzt immer 32MHz  
  
 neu an 1.04
 * defines für nicht negierte (standard Schaltung) und negierten Input 
 
 neu an 1.05
 * Formel 1 Bremslicht hat andere Einschaltdauer 
   
 */

#ifndef DEFINES_H
#define	DEFINES_H


#include "version.h"

#ifdef STANDARD_DECODER
    #define  INPUT_INVERTED             // normale Schaltung mit Eingangs-Transistor
    #undef   INPUT_NOT_INVERTED         // Schaltung nach Marc Walter, Ableitung der                                      
                                        // Überspannung durch Schutzdiode des PIC
#endif

#ifdef DIY_DECODER
    #undef  INPUT_INVERTED              // normale Schaltung mit Eingangs-Transistor
    #define INPUT_NOT_INVERTED          // Schaltung nach Marc Walter, Ableitung der                                      
                                        // Überspannung durch Schutzdiode des PIC
#endif





#define   JA                            1
#define   NEIN                          0
#define   OK                            1
#define   NOK                           0

#define   GEDRUECKT                     0
#define   LOSGELASSEN                   1


#define   LICHTSPERR_ZEIT               133     // 133 x 7,5 ms = 1 sec

#ifdef FORMEL_1_BREMSLICHT
    #define   BREMSLICHT_DAUER          10      // 10 x (ca.)100 ms = 1 sec
#else
    #define   BREMSLICHT_DAUER          5       // 5 x (ca.)100 ms = 0,5 sec
#endif

#define   PROGRAMMIER_TIMEOUT           20      // 20 x (ca.)100 ms = 2 sec


#define   MAX_REGLER                    6       // 6 Regler anschließbar

#define   MAX_DATABITS                  20      // max. Pufferlänge für empf. CU Bits

#define   AUTO_1_ADRESSE                0       // 1. Auto
#define   AUTO_2_ADRESSE                1       // 2. Auto
#define   AUTO_3_ADRESSE                2       // 3. Auto
#define   AUTO_4_ADRESSE                3       // 4. Auto
#define   AUTO_5_ADRESSE                4       // 5. Auto
#define   AUTO_6_ADRESSE                5       // 6. Auto 
#define   GHOSTCAR_ADRESSE              6       // 7. Auto = Ghostcar, Adressierung beginnt mit 0
#define   PACECAR_ADRESSE               7       // 8. Auto = Pacecar, Adressierung beginnt mit 0
#define   PACE_UND_GHOSTCAR_DW_ADRESSE  7       // Pace- und Ghostcar haben eine gemeinsame Datenwort Adressse


#define   PRG_MAX_GESCHWINDIGKEIT       0       // Parameter für Programmierdatenworte
#define   PRG_BREMSWIRKUNG              1
#define   PRG_TANK_INHALT               2
#define   PRG_CU_RESET                  3
#define   PRG_NORMALBETRIEB             4
#define   PRG_TANKSTAND_INFO            10

#define   MIN_BREMSWERT                 6       // minimal von der CU vergebener Bremswert (1. LED blinkt)
#define   MAX_BREMSWERT                 15      // maximal von der CU vergebener Bremswert (5. LED dauer an)
#define   DEFAULT_BREMSWERT             10      // mittlerwer Wert als Defaulteinstellung

#define   AKTIVDATENWORT                8       // Länge des Datenwortes in Bits
#define   REGLERDATENWORT               10      // Länge des Datenwortes in Bits
#define   PROGRAMMIERDATENWORT          13      // Länge des Datenwortes in Bits



/*
 Berechnung PWM Werte der IR LEDs für Auto 1 bis 8
 Timertick ist 4µs bzw, 2 µs @ 32 MHz
 PWM Wert = Periode / Timertick - 1
   
 Auto   Frequenz        Periode/µs   Value PWM 16 MHz     Value PWM 32 MHz  
 1      15,625           64             15                  31
 2      7,8125          128             31                  63
 3      5,208333333     192             47                  95
 4      3,90625         256             63                  127  
 5      3,125           320             79                  159
 6      2,604166667     384             95                  191 
 7      2,232142857     448            111                  223
 8      1,953125        512            127                  255
 */

#define   IR_LED_PWM_CAR_1               31 
#define   IR_LED_PWM_CAR_2               63
#define   IR_LED_PWM_CAR_3               95
#define   IR_LED_PWM_CAR_4              127
#define   IR_LED_PWM_CAR_5              159  
#define   IR_LED_PWM_CAR_6              191
#define   IR_LED_PWM_CAR_7              223
#define   IR_LED_PWM_CAR_8              255


#define   PULS_START                    1
#define   PULS_KURZ                     2
#define   PULS_LANG                     3

//-------------------------------------------------- Pulslängen in µs zur Auswertung Manchester Code

#define   PULS_START_MIN                300
#define   PULS_START_MAX                7500

// kurz und lang unterschiedliche Pulsweiten für High und Low
                                        // kurze Pulse normal 50, gemessen High 35, Low 65
#define   HIGH_PULS_KURZ_MIN            25  // alt 25
#define   HIGH_PULS_KURZ_MAX            65  // alt 75
#define   LOW_PULS_KURZ_MIN             35  // alt 25
#define   LOW_PULS_KURZ_MAX             75  // alt 75

                                        // lange Pulse normal 100, gemessen High 90, Low 110
#define   HIGH_PULS_LANG_MIN            75  // alt 75
#define   HIGH_PULS_LANG_MAX            120 // alt 120
#define   LOW_PULS_LANG_MIN             85  // alt 75
#define   LOW_PULS_LANG_MAX             130 // alt 120



/*
// kurz und lang gleiche Pulsweiten für High und Low
#define   HIGH_PULS_KURZ_MIN            25  // alt 25
#define   HIGH_PULS_KURZ_MAX            75  // alt 75
#define   LOW_PULS_KURZ_MIN             25  // alt 25
#define   LOW_PULS_KURZ_MAX             75  // alt 75

                                         // lange Pulse normal 100, gemessen High 90, Low 110
#define   HIGH_PULS_LANG_MIN            75  // alt 75
#define   HIGH_PULS_LANG_MAX            120 // alt 120
#define   LOW_PULS_LANG_MIN             75  // alt 75
#define   LOW_PULS_LANG_MAX             120 // alt 120
*/



#define   PULS_UNBEKANNT                0
#define   PULS_START                    1
#define   PULS_KURZ_HIGH                2
#define   PULS_KURZ_LOW                 3
#define   PULS_LANG_HIGH                4
#define   PULS_LANG_LOW                 5


#endif	/* DEFINES_H */

