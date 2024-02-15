/*****************************************************************************/

/// \file       Decoder.c
/// \author     Frank Redlich
/// \version    1.03
/// \date       07.10.2021
/// \brief      Spezielle Routinen f�r den Decoder
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a, DIY, DIY2

/******************************************************************************/
/*
 * neu an 1.01
 * - Werte f�r 32MHz Takt
 * - Fahrtabelle als 2 dimensionales Feld
  
 * neu an 1.02
 * - Kombi- oder separate R�ck- und Bremslichter m�glich
 * 
 * neu in 1.03 [MiZu]
 * - It was possible to program car to different ID without power cycle.
 *   This worked by putting the car in ready for power cycle mode with one ID
 *   and then set the ID with another controller. Version 1.02 disregards if 
 *   there really was a power cycle. I did not change this, as there might be 
 *   timing issues to recognize power cycle or not. I made sure that the 
 *   programming and the preparing for programming is done from same 
 *   controller ID. 
 */


//#include <xc.h> microchip specific stuff
#include "typedef.h"
#include "ports.h"
#include "variable.h"
#include "eeprom.h"
#include "init.h"
#include "delays.h"

#include "decoder.h"



// Registerwerte zum Bremsen (CCP2)
// Die CU hat 10 Einstellm�glichkeiten
//const U8    Bremstabelle[]   = {137,151,163,175,189,200,213,227,239,255};

// Registerwerte zum Bremsen (CCP2)
// alle 16 M�glichkleiten von OpenLap
//const U8    Bremstabelle[]   = { 62,  76,  88, 100, 115, 126,                                     // zus�tzliche Werte von Open Lap
//                                137, 151, 163, 175, 189, 200, 213, 227, 239, 255};                // CU Werte

// Registerwerte zum Bremsen (CCP2)
// alle 16 M�glichkleiten von OpenLap
// Werte f�r PWM max = 128 (wenn der PIC mit 32 MHz l�uft)
const U8    Bremstabelle[]   = { 31,  38,  44,  50,  57,  63,                                     // zus�tzliche Werte von Open Lap
                                 68,  75,  81,  87,  94, 100, 106, 113, 119, 127};                // CU Werte


/*
// Registerwerte zum Fahren (CCP1)
// Die CU hat 10 Einstellm�glichkeiten (1..15 mit L�cken)
// Via Fahrregler k�nnen 16 Fahrstufen gew�hlt werden
// Werte f�r PWM max = 256
const U8    Fahrtabelle_0[]  = {  0,  3,  6, 11, 14, 19, 22, 26, 30, 34, 38, 42, 45, 50, 53, 62};  // 
const U8    Fahrtabelle_1[]  = {  0,  4,  8, 14, 18, 24, 28, 32, 38, 42, 48, 52, 56, 62, 66, 76};  // 1. LED blinkt
const U8    Fahrtabelle_2[]  = {  0,  4, 10, 16, 22, 28, 32, 38, 44, 50, 56, 60, 66, 72, 78, 88};  // 1. LED an
const U8    Fahrtabelle_3[]  = {  0,  6, 13, 22, 28, 34, 40, 46, 52, 58, 64, 70, 76, 82, 88,100};  // 2. LED blinkt
const U8    Fahrtabelle_4[]  = {  0,  7, 15, 23, 30, 37, 44, 51, 58, 65, 72, 79, 86, 93,100,115};  // 
const U8    Fahrtabelle_5[]  = {  0,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96,104,112,126};  // 2. LED an
const U8    Fahrtabelle_6[]  = {  0,  8, 16, 26, 36, 44, 56, 64, 72, 80, 88, 96,104,113,122,138};  // 3. LED blinkt
const U8    Fahrtabelle_7[]  = {  0,  8, 18, 28, 38, 48, 56, 66, 76, 86, 96,104,114,124,133,152};  // 3. LED an
const U8    Fahrtabelle_8[]  = {  0,  9, 20, 32, 41, 52, 62, 72, 83, 94,104,114,125,136,147,165};  // 
const U8    Fahrtabelle_9[]  = {  0, 10, 22, 35, 44, 56, 67, 78, 90,101,112,124,136,148,160,176};  // 4. LED blinkt
const U8    Fahrtabelle_10[] = {  0, 11, 23, 37, 48, 60, 72, 84, 96,108,120,132,144,157,169,190};  // 
const U8    Fahrtabelle_11[] = {  0, 12, 24, 38, 51, 64, 76, 89,102,115,128,140,152,165,178,202};  // 4. LED an
const U8    Fahrtabelle_12[] = {  0, 13, 26, 41, 55, 68, 81, 95,108,122,136,149,162,176,189,215};  // 
const U8    Fahrtabelle_13[] = {  0, 14, 28, 43, 58, 72, 86,100,114,129,144,158,172,186,200,228};  // 5. LED blinkt
const U8    Fahrtabelle_14[] = {  0, 15, 30, 46, 61, 76, 91,106,121,137,152,167,182,197,212,240};  // 
const U8    Fahrtabelle_15[] = {  0, 16, 32, 48, 64, 80, 96,112,128,144,160,176,192,208,224,255};  // 5. LED an
*/


// Registerwerte zum Fahren (CCP1)
// Die CU hat 10 Einstellm�glichkeiten (1..15 mit L�cken)
// Via Fahrregler k�nnen 16 Fahrstufen gew�hlt werden
// Werte f�r PWM max = 128
const U8    Fahrtabelle[16][16]  = { 0, 2,  3,  6,  7, 10, 11, 13, 15, 17, 19, 21, 22,  25,  26,  31,  // 
                                     0, 2,  4,  7,  9, 12, 14, 16, 19, 21, 24, 26, 28,  31,  33,  38,  // 1. LED blinkt
                                     0, 2,  5,  8, 11, 14, 16, 19, 22, 25, 28, 30, 33,  36,  39,  44,  // 1. LED an
                                     0, 3,  7, 11, 14, 17, 20, 23, 26, 29, 32, 35, 38,  41,  44,  50,  // 2. LED blinkt
                                     0, 4,  7, 12, 15, 19, 22, 26, 29, 33, 36, 40, 43,  47,  50,  58,  // 
                                     0, 4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,  52,  56,  63,  // 2. LED an
                                     0, 4,  8, 13, 18, 22, 28, 32, 36, 40, 44, 48, 52,  57,  61,  69,  // 3. LED blinkt
                                     0, 4,  9, 14, 19, 24, 28, 33, 38, 43, 48, 52, 57,  62,  67,  76,  // 3. LED an
                                     0, 5, 10, 16, 21, 26, 31, 36, 42, 47, 52, 57, 63,  68,  73,  83,  // 
                                     0, 5, 11, 18, 22, 28, 34, 39, 45, 51, 56, 62, 68,  74,  80,  88,  // 4. LED blinkt
                                     0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 72,  78,  85,  95,  // 
                                     0, 6, 12, 19, 26, 32, 38, 45, 51, 58, 64, 70, 76,  83,  89, 101,  // 4. LED an
                                     0, 7, 13, 20, 27, 34, 41, 47, 54, 61, 68, 75, 81,  88,  95, 108,  // 
                                     0, 7, 14, 22, 29, 36, 43, 50, 57, 65, 72, 79, 86,  93, 100, 114,  // 5. LED blinkt
                                     0, 8, 15, 23, 31, 38, 46, 53, 61, 68, 76, 84, 91,  99, 106, 120,  // 
                                     0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 127}; // 5. LED an


/******************************************************************************/

/**
 * wertet ein empfangenes Regler oder Ghostcar Datenwort aus
 * Datenwort steht in DataBit[]
 */
void Reglerdatenwort_decodieren(void)
{
    U8      Auto_Adresse,
            Reglerwert;


    Auto_Adresse = 0;
    if (DataBit[1] == 1)
        Auto_Adresse |= 0x04;
    if (DataBit[2] == 1)
        Auto_Adresse |= 0x02;
    if (DataBit[3] == 1)
        Auto_Adresse |= 0x01;
    CU_Daten.Adresse = Auto_Adresse;
    
    CU_Daten.Spurwechseltaste = DataBit[4];

    Reglerwert = 0;                 // wird sp�ter in PWM geschrieben
    if (DataBit[5] == 1)
        Reglerwert |= 0x08;
    if (DataBit[6] == 1)
        Reglerwert |= 0x04;
    if (DataBit[7] == 1)
        Reglerwert |= 0x02;
    if (DataBit[8] == 1)
        Reglerwert |= 0x01;
    CU_Daten.Reglerwert = Reglerwert;

    CU_Daten.Tankanzeige = DataBit[9];


}
/******************************************************************************/

/**
 * wertes ein empfangenes Programmierdatenwort aus
 * Datenwort steht in DataBit[]
 * Ergebnis steht in der globalen Struktur CU_Prg_Daten
 */
void Programmierdatenwort_decodieren(void)
{
    U8      Adresse,
            Parameter,
            Wert;


    Wert = 0;
    if (DataBit[1] == 1)
        Wert |= 0x01;
    if (DataBit[2] == 1)
        Wert |= 0x02;
    if (DataBit[3] == 1)
        Wert |= 0x04;
    if (DataBit[4] == 1)
        Wert |= 0x08;
    CU_Prg_Daten.Wert = Wert;

    Parameter = 0;
    if (DataBit[5] == 1)
        Parameter |= 0x01;
    if (DataBit[6] == 1)
        Parameter |= 0x02;
    if (DataBit[7] == 1)
        Parameter |= 0x04;
    if (DataBit[8] == 1)
        Parameter |= 0x08;
    if (DataBit[9] == 1)
        Parameter |= 0x10;
    CU_Prg_Daten.Parameter = Parameter;

    Adresse = 0;
    if (DataBit[10] == 1)
        Adresse |= 0x01;
    if (DataBit[11] == 1)
        Adresse |= 0x02;
    if (DataBit[12] == 1)
        Adresse |= 0x04;
    CU_Prg_Daten.Adresse = Adresse;
}



/******************************************************************************/

/**
 * je nach CU Datenwort Reglerwert in's PWM 1 Register f�r Motor schreiben
 * den wert in der globalen Variable Motor_PWM_Wert merken
 * je nach CU Datenwort Reglerwert in's PWM 2 Register f�r Bremse schreiben
 * Wenn Motor an, dann Licht_Sperr_Timer setzen
 * 
 */
void Motor_und_Bremse_ansteuern(U8 Wert)
{
    U8      Bremswirkung,
            v_max,
            Motor_PWM_Wert;
    
    
                                                                                // Fehelerhaften Werten vorbeugen 
    v_max =        (U8)(EE_read(EE_ADR_MAX_GESCHWINDIGKEIT) & 0x0F);            // zur Sicherheit die Werte jedesmal neu auslesen
    Bremswirkung = (U8)(EE_read(EE_ADR_BREMSWIRKUNG) & 0x0F);
    Wert         = (U8)(Wert & 0x0F);
    
    Motor_PWM_Wert = Fahrtabelle[v_max][Wert];
    
    if ((Motor_PWM_Wert == 0) && (Letzter_Zustand_Bremse == LOSGELASSEN))       // Motor aus, Bremse ist noch aus
    {
        Bremslicht_timer = BREMSLICHT_DAUER;                                    // dann f�r ein paar Sekunden das Bremslicht einschalten
       // CCPR1L = 0;      todo: gpio write pin                                                      // Motor ausschalten
        delay_100us();                                                          // zur Sicherheit kurz warten
        //CCPR2L = Bremstabelle[Bremswirkung]; todo: gpio write pin
            
        Letzter_Zustand_Bremse = GEDRUECKT;
    }

    if ((Motor_PWM_Wert != 0) && (Letzter_Zustand_Bremse == GEDRUECKT))         // Motor an, Bremse ist noch gedr�ckt
    {
        //CCPR2L = 0;             todo: gpio write pin                                                // Bremse l�sen
        delay_100us();                                                          // zur Sicherheit kurz warten
        //CCPR1L = Motor_PWM_Wert; todo: gpio write pin

        Letzter_Zustand_Bremse = LOSGELASSEN;
    }

    if ((Motor_PWM_Wert != 0) && (Letzter_Zustand_Bremse == LOSGELASSEN))       // Motor an, Bremse ist schon gel�st
    {
        //CCPR2L = 0; todo gpio                                                             // Bremse aus (zur Sicherheit)
        //CCPR1L = Motor_PWM_Wert; todo gpio                                                // Motor entsprechend Reglerstellung ansteuern
        Licht_Sperr_Timer = LICHTSPERR_ZEIT;
    }

    if ((Motor_PWM_Wert == 0) && (Letzter_Zustand_Bremse == GEDRUECKT))         // Motor aus, Bremse ist schon angezogen
    {
        //CCPR1L = 0; todo gpio                                                            // Motor aus (zur Sicherheit)
        //CCPR2L = Bremstabelle[Bremswirkung]; todo gpio
    }
        
}

/******************************************************************************/

/**
 * f�r alle 6 Regler das Dr�cken der Spurwechseltaste z�hlen
 * wenn 2 x gedr�ckt und Motor aus dann in den Programmiermodus
 * wenn im Programmiermodus 2x gedr�ckt, dann die neue Adresse speichern
 */
void Count_Spurwechseltaste(U8 Adresse)
{
    U16  index,
         index_2;

    if (
            (Spurwechseltaste.Letzter_Zustand[Adresse] == LOSGELASSEN) &&
            (CU_Daten.Spurwechseltaste == GEDRUECKT)
        )
    {
        if (CU_Daten.Reglerwert == 0)                                           // Nur wenn Auto wo die taste gedr�ckt wurde steht
        {
            Spurwechseltaste.Counter[Adresse]++;
            Spurwechseltaste.Reset_Timer[Adresse] = PROGRAMMIER_TIMEOUT;        // 2 Sekunden, wenn dann keine Taste gedr�ckt, dann counter l�schen

            Programmiermodus = EE_read(EE_ADR_PROGRAMMIERMODUS);            
            if (Spurwechseltaste.Counter[Adresse] == 2)                         // 2 x Taste gedr�ckt
            {
                if (Programmiermodus == NEIN)                                   // wenn kein Programmiermodus ist
                {
                    EE_write_verified (Adresse+1, EE_ADR_PROGRAMMIERMODUS);     // Programmiermodus Adresse lernen einschalten, [MiZu] merken welcher Controller]
                    Adr_warte_auf_Reset_timeout = PROGRAMMIER_TIMEOUT;          // wenn 2 Sekunden kein Neustart dann EEPROM wieder r�ckstellen
                }                                                               // wird erst nach Neustart wirksam

                if (Programmiermodus == (Adresse+1))                            // [MiZu] erfordert aktivierung Programmiermodus und programmierung durch selben Controller
                {
                    Programmiermodus = NEIN;                                    // Programmiermodus beenden
                    EE_write_verified (NEIN, EE_ADR_PROGRAMMIERMODUS);          // und das auch merken
                    Adr_Programmier_timeout = 0;
                    eigene_Adresse = Adresse;                                   // neue eigene Adresse
                    EE_write_verified (Adresse, EE_ADR_AUTO_ADRESSE);           // eigene Adresse merken
                    Licht_einschalten();                                        // Licht einschalten
                    Licht_Sperr_Timer = LICHTSPERR_ZEIT;
                    IR_LED_einschalten();                                       // IR LED Frequenz lt. Auto einstellen
                    
                    for (index = 0; index < 20; index++)                        // kurz mit dem Motor ruckeln
                    {
                        //CCPR2L = 0; todo: gpio write pin                                            // Bremse abschalten
                        delay_100us;
                        //CCPR1L = 100; todo: gpio write pin                                           // Motor einschalten
                        for (index_2 = 0; index_2 < 100; index_2++)
                             delay_100us;
                        //CCPR1L = 0;      todo gpio                                       // Motor abschalten
                        for (index_2 = 0; index_2 < 100; index_2++)
                             delay_100us;
                    }

                    Ghostcar_Doppelklick_timeout = PROGRAMMIER_TIMEOUT;         // 2 sec Zeit f�r Doppelklick um in Ghostcarmodus zu kommen
                    Ghostcar_Doppelklick_Counter = 0;                           // zum Z�hlen von 2 weiteren Klicks
                    Spurwechseltaste.Counter[Adresse] = 0;
                }
            }
        }
    }

    if ((Spurwechseltaste.Letzter_Zustand[Adresse] == GEDRUECKT) &&
        (CU_Daten.Spurwechseltaste == LOSGELASSEN))
    {
        NOP();
    }


    Spurwechseltaste.Letzter_Zustand[Adresse] = CU_Daten.Spurwechseltaste;
}

/******************************************************************************/

/**
 * schaltet das Licht um wenn die Spurwechseltaste gedr�ckt wurde
 * wechselt u.U. in den Ghostcar Geschwindigkeitsprogrammiermode
 *               oder in den Gostcarmode
 * nur wenn der Motor min 1 sec aus ist
 */
void Eigene_Spurwechseltaste_auswerten(void)
{
    if ((Letzter_Zustand_Licht_Taste == LOSGELASSEN) &&
        (CU_Daten.Spurwechseltaste == GEDRUECKT))
    {
        if(Licht_Sperr_Timer == 0)                                              // Nur wenn der Motor schon etwas aus ist
        {            
            Licht^= 1;
            if (Licht == 0)
            	;
               // Pin_o_LICHT = 0; todo: macro gegen was anderes ersetzen                                               // Licht umschalten
            else
               // Pin_o_LICHT = 1; todo: macro gegen was anderes ersetzen                                               // Licht umschalten
            EE_write (Licht, EE_ADR_LICHT);                                     // und merken
        }

        if (Ghostcar_Doppelklick_timeout > 0)                                   // wenn gerade Zeitfenster f�r Doppelklick f�r Ghostcarmode offen ist
        {
            Ghostcar_Doppelklick_Counter++;
            if (Ghostcar_Doppelklick_Counter == 3)                              // Ein Klick war schon vorher da
            {
                Ghostcar_Doppelklick_timeout = 0;                               // warten auf den Doppelklick abbrechen
                Ghostcar_Programmiermodus = JA;
                EE_write_verified(Ghostcar_Programmiermodus, EE_ADR_GHOST_PROGRAMMIERMODUS);
            }
        }
        else
        {
            Ghostcar_Programmiermodus = EE_read(EE_ADR_GHOST_PROGRAMMIERMODUS);                    
            if (Ghostcar_Programmiermodus == JA)                                // Wenn gerade die Ghostcar Geschwindigkeit eingestellt wird
            {
                Ghostcar_Programmiermodus = NEIN;                               // dann Ghostcar Programmiermodus beenden
                EE_write_verified(Ghostcar_Programmiermodus, EE_ADR_GHOST_PROGRAMMIERMODUS);
                if (CU_Daten.Reglerwert > 0)                                    // wenn die Geschwindigkeit > 0 ist
                {
                    v_Ghostcar = CU_Daten.Reglerwert;
                    EE_write_verified(v_Ghostcar, EE_ADR_GHOST_GESCHWINDIGKEIT);
                    eigene_Adresse = GHOSTCAR_ADRESSE;
                    EE_write_verified(eigene_Adresse, EE_ADR_AUTO_ADRESSE);
                    Licht_einschalten();                                        // Licht einschalten
                    Licht_Sperr_Timer = LICHTSPERR_ZEIT;
                    IR_LED_einschalten();                                       // IR Frequenz auf Ghostcar
                }
             }
        }
    }

    if ((Letzter_Zustand_Licht_Taste == GEDRUECKT) &&
        (CU_Daten.Spurwechseltaste == LOSGELASSEN))
    {
        NOP();
    }

    Letzter_Zustand_Licht_Taste = CU_Daten.Spurwechseltaste;

}

/******************************************************************************/

/**
 * schaltet in Abh�ngigkeit vom EEPROM Wert das Licht ein oder aus
 */
void Licht_schalten (void)
{
    Licht = EE_read(EE_ADR_LICHT);
    
    if (Licht == 0)                 // Zustand Licht wieder herstellen
    	;
        //Pin_o_LICHT = 0; todo makro gpio
    else
        //Pin_o_LICHT = 1; todo makro gpio
    	;
}

/******************************************************************************/

/**
 * Licht einschalten und speichern
 */
 void Licht_einschalten (void)
 {
     Licht = 1;
     //Pin_o_LICHT = 1; todo makro gpio
     EE_write (Licht, EE_ADR_LICHT);
 }

/******************************************************************************/
/**
 * es wurde ein CU Programmierdatenwort mit der eigenen Adresse empfangen
 * Bremswert und max. Geschwindigkeit wird eingespeichert
 * der Rest wird ignoriert
 */
void Parameter_verarbeiten(void)
{
    U8      Bremswirkung,
            v_max;
    
    
    switch(CU_Prg_Daten.Parameter)
    {
        case PRG_MAX_GESCHWINDIGKEIT:
            if (CU_Prg_Daten.Wert <= 15)                                        // Wert muss kleiner 15 sein            
            {
                v_max = CU_Prg_Daten.Wert;
                EE_write_verified(v_max, EE_ADR_MAX_GESCHWINDIGKEIT);
            }
            break;
        case PRG_BREMSWIRKUNG:
            if (CU_Prg_Daten.Wert <= 15)                                        // Wert muss kleiner 15 sein
            {
                Bremswirkung = CU_Prg_Daten.Wert;
                EE_write_verified(Bremswirkung, EE_ADR_BREMSWIRKUNG);
            }
            break;
        case PRG_TANK_INHALT:
            break;
        case PRG_CU_RESET:
            break;
        case PRG_NORMALBETRIEB:
            break;
    }
}

/******************************************************************************/


/**
 * schaltet die PWM Frequenz der IR LED entsprechend der Auto Nummer
 */
void IR_LED_einschalten(void)
{    
    eigene_Adresse = EE_read(EE_ADR_AUTO_ADRESSE);
    switch (eigene_Adresse)
    {
        case AUTO_1_ADRESSE:
            Init_CCP3(IR_LED_PWM_CAR_1);             // CCP3 f�r IR LED
            break;
        case AUTO_2_ADRESSE:
            Init_CCP3(IR_LED_PWM_CAR_2);             // CCP3 f�r IR LED
            break;
        case AUTO_3_ADRESSE:
            Init_CCP3(IR_LED_PWM_CAR_3);             // CCP3 f�r IR LED
            break;
        case AUTO_4_ADRESSE: 
            Init_CCP3(IR_LED_PWM_CAR_4);             // CCP3 f�r IR LED
            break;
        case AUTO_5_ADRESSE: 
            Init_CCP3(IR_LED_PWM_CAR_5);             // CCP3 f�r IR LED
            break;
        case AUTO_6_ADRESSE: 
            Init_CCP3(IR_LED_PWM_CAR_6);             // CCP3 f�r IR LED
            break;
        case GHOSTCAR_ADRESSE:                       // Adresse 6
            Init_CCP3(IR_LED_PWM_CAR_7);             // CCP3 f�r IR LED
            break;
        //case PACECAR_ADRESSE:                       // Adresse 7
        //    Init_CCP3(IR_LED_PWM_CAR_8);            // CCP3 f�r IR LED
        //    break;
    }

}

/*****************************************************************************************************/
