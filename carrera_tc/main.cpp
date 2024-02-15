/*
 * main.cpp
 *
 *  Created on: Feb 15, 2024
 *      Author: simon
 */
#include "main.h"

//#include <xc.h> microchip specific stuff
#include "version.h"
#include "typedef.h"
#include "defines.h"
#include "variable.h"
#include "ports.h"
#include "init.h"
#include "decoder.h"
#include "eeprom.h"
#include "delays.h"

//microchip specific stuff

//#pragma config FCMEN = OFF              // Fail-Safe Clock Monitor disabled
//#pragma config IESO = OFF               // Internal/External Switchover mode is disabled
//#pragma config CLKOUTEN = OFF           // CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
////#pragma config BOREN = OFF              // Brown-out Reset disabled
//#pragma config BOREN = ON               // Brown-out Reset enabled
//#pragma config CPD = OFF                // Data memory code protection is disabled
//#pragma config CP = OFF                 // Program memory code protection is disabled
//#pragma config MCLRE = OFF              // MCLR/VPP pin function is digital input
//
//#pragma config PWRTE = OFF              // power up timer disabled
////#pragma config PWRTE = ON               // power up timer enabled     (seltsamerweise geht der Reset hier ca 64ms schneller)
//
////#pragma config WDTE = OFF               // Watchdogtimer disabled
////#pragma config WDTE = ON                // Watchdogtimer always enabled
//#pragma config WDTE = SWDTEN            // WDT controlled by the SWDTEN bit in the WDTCON register
//
//#pragma config FOSC = INTOSC            // INTOSC oscillator: I/O function on CLKIN pin
//
//#pragma config LVP = ON                 // Low-voltage programming enabled
////#pragma config BORV = HI                // Brown-out Reset Voltage (VBOR) set to 2.7 V
//#pragma config BORV = LO                // Brown-out Reset Voltage (VBOR) set to 1.9 V
//#pragma config STVREN = OFF             // Stack Overflow or Underflow will not cause a Reset
//
//#pragma config PLLEN = ON               // 4xPLL enabled
//
//#pragma config WRT = OFF                // Write protection off

extern "C" void mainInit();
extern "C" void mainProcces();

U8 Adresse;

void mainInit()  {
   // U8      Adresse; todo weil main aufgeteilt wurde wird diese variable global


//    OSCCONbits.IRCF = 0b1110;                                                   // interner Oszillator auf 8 MHz (4xPLL = 32 MHz)

    Initialisierung();                                                          // Ports, Timer etc.

    Init_EEPROM_Defaultwerte();


//    WDTCONbits.SWDTEN = 1;                                                      // Watchdog einschalten
//    CLRWDT();                                                                   // clear Watchdog

    //--------------------------------------------------------------------------

    Licht_schalten();                                                           // je nach Wert im EEPROM Licht ein oder aus
    IR_LED_einschalten();                                                       // mit der Frequenz entsprechend der Car Adresse

    //--------------------------------------------------------------------------
    //if ((EE_read(EE_ADR_PROGRAMMIERMODUS)) == JA)                               // Auto Adresse Programmiermodus JA/NEIN
    if ((EE_read(EE_ADR_PROGRAMMIERMODUS)) != NEIN)                             // Auto Adresse Programmiermodus NEIN, [MiZu] oder Controller ID, die Programmierung angefordert hat
        Adr_Programmier_timeout = PROGRAMMIER_TIMEOUT;                          // ca. 3 sec Programmierm�glichkeit f�r Adresse
    else
        Adr_Programmier_timeout = 0;

}

void mainProcces() {
	if (Telegramm_empfangen == JA)                                          // alle 7,5 msec
	        {
//	            CLRWDT();                                                           // clear Watchdog

	            Telegramm_empfangen = NEIN;

	            DataBit[0] = 'X';                                                   // Startbit ung�ltig machen f�r erneutemn Empfang
	            Timer_Counter++;                                                    // allgemeiner Timer 7,5 ms

	            //...................................................

	            if (Licht_Sperr_Timer > 0)                                          // auf Null z�hlen
	                Licht_Sperr_Timer--;                                            // jetzt darf Licht geschaltet werden

	            eigene_Adresse = (U8)(EE_read(EE_ADR_AUTO_ADRESSE) & 0x07);         // wird in dieser Routine mehrfach ben�tigt

	            switch (Telegrammtyp)
	            {
	                case AKTIVDATENWORT:     //.....................................   Aktivdatenwort

	                    if (CU_Daten.Adresse < 6)                                   // nur normale Autos, kein Ghostcar
	                    {
	                        if (DataBit[eigene_Adresse + 1] == 0)                   // wenn der eigene Regler nicht gedr�ckt
//	                            CCPR1L = 0;      todo gpio
	                        	;// Motor ausschalten
	                    }
	                    break;

	                case REGLERDATENWORT: //........................................  Regler oder Ghostcar Datenwort

	                    Reglerdatenwort_decodieren();

	                    if (
	                            (Ghostcar_Doppelklick_timeout == 0) &&              // nur wenn nicht auf Doppelklick f�r Ghostcar gewartet wird
	                            (CU_Daten.Adresse < 6)
	                        )
	                        Count_Spurwechseltaste(CU_Daten.Adresse);

	                    if (CU_Daten.Adresse == eigene_Adresse)
	                    {
	                        Motor_und_Bremse_ansteuern(CU_Daten.Reglerwert);        // Motor in Abh�ngigkeit der Reglerstellung
	                        if (Tank_leer == JA)                                    // wenn Tank leer dann blinken ==> kommt aus einem Programmierdatenwort
	                            Tank_leer_Blinken = JA;

	                        Eigene_Spurwechseltaste_auswerten();                    // Schalten von Licht bzw. Wechsel in Ghostcarprogrammierung

	                        if (Adr_warte_auf_Reset_timeout > 0)                    // wenn 2x Spurwechseltaste gedr�ckt gedr�ckt aber noch nicht angehoben
	                        {
	                            if (CU_Daten.Reglerwert > 0)                        // und wenn das Auto f�hrt
	                                Adr_warte_auf_Reset_timeout = 1;                // dann beim n�chstenTimerclick den Programmiermodus sofort verlassen
	                        }
	                    }

	                    if (eigene_Adresse == GHOSTCAR_ADRESSE)                     // Ghostcarbetrieb
	                    {
	                        v_Ghostcar = (U8)(EE_read(EE_ADR_GHOST_GESCHWINDIGKEIT) & 0x0F);

	                        if (CU_Daten.Adresse == PACE_UND_GHOSTCAR_DW_ADRESSE)
	                        {
	                            CU_Daten.KFR = DataBit[4];                          // Keine Freigabe Bit
	                            CU_Daten.FR = DataBit[6];                           // Freigabe Bit
	                            if ((CU_Daten.KFR == 0) && (CU_Daten.FR == 1))
	                                Motor_und_Bremse_ansteuern(v_Ghostcar);         // programmierte Geschwindigkeit
	                            if ((CU_Daten.KFR == 1) && (CU_Daten.FR == 0))
	                                Motor_und_Bremse_ansteuern(0);                  // Motor aus, z.B. in Startphase
	                        }
	                    }

	                    break;

	                case PROGRAMMIERDATENWORT: //.................................  Programmierdatenwort
	                    Programmierdatenwort_decodieren();
	                    if (CU_Prg_Daten.Adresse == eigene_Adresse)
	                    {
	                        if (                                                    // das wid immer 2 x �bertragen
	                                (CU_Prg_Daten.Parameter == PRG_MAX_GESCHWINDIGKEIT) ||
	                                (CU_Prg_Daten.Parameter == PRG_BREMSWIRKUNG) //||
	                                //(CU_Prg_Daten.Parameter == TANK_INHALT)
	                            )
	                        {
	                            //. . . . . . . . . . . . . . . . . . . . . . . . .    max. Geschwindigkeit oder Bremswirkung
	                            if (                                                // Wenn das Parametrierwort schon mal gesendet wurde
	                                    (CU_Prg_Daten.Parameter == CU_Prg_Daten.Parameter_alt) &&
	                                    (CU_Prg_Daten.Wert == CU_Prg_Daten.Wert_alt)
	                               )

	                            {
	                                Parameter_verarbeiten();                        // max. Gewschindigkeit und Bremswirkung speichern
	                                CU_Prg_Daten.Parameter_alt = PRG_NORMALBETRIEB;
	                                CU_Prg_Daten.Wert_alt = 0;
	                            }
	                            else
	                            {
	                                CU_Prg_Daten.Parameter_alt = CU_Prg_Daten.Parameter;// merken was gerade gesendet wurde
	                                CU_Prg_Daten.Wert_alt = CU_Prg_Daten.Wert;
	                            }
	                        }
	                        else
	                        {
	                            if (CU_Prg_Daten.Parameter == PRG_NORMALBETRIEB)
	                            {
	                                if ((CU_Prg_Daten.Wert & 0x08) != 0)
	                                    Tank_leer = JA;
	                                else
	                                    Tank_leer = NEIN;
	                            }
	                        }

	                    }
	                    break;

	            }

	            //----------------------------------------------------------------  ab hier alle ca. 100msec
	            //if (Timer_Counter > 13)                                           // wenn alle Telegramme detektiert werden
	            if (Timer_Counter > 10)                                             // wenn die Aktivdatenw�rter nicht detektiert werden
	            {
	                Timer_Counter = 0;



	                //..............................................................
	                if (Adr_warte_auf_Reset_timeout > 0)                            // Programmiersequenz ist gestartet aber es ist noch kein Neustart gewesen
	                {
	                    Adr_warte_auf_Reset_timeout--;
	                    if (Adr_warte_auf_Reset_timeout == 0)                       // wenn 2 Sekunden kein Neuart
	                    {
	                        Programmiermodus = NEIN;                                // dann Programmiermodus verlassen
	                        EE_write_verified (NEIN, EE_ADR_PROGRAMMIERMODUS);
	                    }
	                }

	                //..............................................................
	                if (Adr_Programmier_timeout > 0)                                // Programmiermodus nach Neustart nach 2 Sekunden abbrechen
	                {
	                    //Pin_o_LICHT ^= 1; gpio makro
	                    Adr_Programmier_timeout--;                                  // Timeout f�r Adresssierung Auto Adresse
	                    if (Adr_Programmier_timeout == 0)
	                    {
	                        Programmiermodus = NEIN;                                // dann Programmiermodus verlassen
	                        EE_write_verified (NEIN, EE_ADR_PROGRAMMIERMODUS);
	                        Licht_schalten();                                       // je nach Wert im EEPROM Licht ein oder aus
	                    }
	                }

	                //..............................................................
	                if (Ghostcar_Doppelklick_timeout > 0)                           // Zeitfenster f�r Doppelklick nach Adr.-Programmierung
	                    Ghostcar_Doppelklick_timeout--;                             // beenden


	                //..............................................................
	                if (Bremslicht_timer > 0)
	                {
	                    Bremslicht_timer--;

	                    #ifdef FORMEL_1_BREMSLICHT

	                    if ((Bremslicht_timer & 0x01) != 0)
	                        Pin_o_BREMSLICHT = 1;
	                    else
	                        Pin_o_BREMSLICHT = 0;
	                    #else
	                        //Pin_o_BREMSLICHT = 1; todo gpio makro
	                        //CCPR4L = 0xFE; todo pwm brems lich low prio                                              // PWM f�r Bremslicht voll auf
	                    #endif
	                }
	                else
	                {
	                    //Pin_o_BREMSLICHT = 0;        todo gpio                               // Bremslicht aus

	                    if (true/*Pin_o_LICHT == 1*/)    //todo makro scheiss                                   // wenn Licht an, dann R�cklicht glimmen lassen
	                        #ifdef KOMBI_LEUCHTEN
	                        //CCPR4L = 0x10; todo pwm oder so
	                        #endif

	                        #ifdef SEPARATE_LEUCHTEN
	                       // CCPR4L = 0x00; todo gpio
	                        #endif
	                    	;
	                    else
	                    	;
	                        //CCPR4L = 0x00; todo gpio                                          // sonst R�cklicht ganz aus
	                }

	                //..............................................................
	                for (Adresse = 0; Adresse < MAX_REGLER; Adresse++)              // f�r alle Regler
	                {
	                    if (Spurwechseltaste.Reset_Timer[Adresse] > 0)              // wenn 2 Sekunden keine Taste gedr�ckt, dann
	                    {                                                           // den Counter l�schen
	                        Spurwechseltaste.Reset_Timer[Adresse]--;                // d.h. zum Programmieren muss die Taste 2 x innerhalb
	                        if (Spurwechseltaste.Reset_Timer[Adresse] == 0)         // von 2 Sekunden gedr�ckt werden
	                        {
	                            Spurwechseltaste.Counter[Adresse] = 0;
	                        }
	                    }
	                }


	                //..............................................................

	                Ghostcar_Programmiermodus = EE_read(EE_ADR_GHOST_PROGRAMMIERMODUS);
	                if (
	                        (Ghostcar_Programmiermodus == JA) ||
	                        (Tank_leer_Blinken == JA)
	                    )
	                                                                                // Im Ghostcar Programmiermodus (Geschwindigkeit einstellen)
	                                                                                // und wenn der Tank leer ist, dann
	                {                                                               // langsam blinken
	                   // Pin_o_LICHT ^= 1; todo makro gpio

	                    if ((Tank_leer_Blinken == JA) && (Tank_leer == NEIN))       // wenn Tank wieder voll, dann Licht schalten wie es war
	                    {
	                        Tank_leer_Blinken = NEIN;                               // aufh�ren mit Blinken
	                        Licht_schalten();
	                    }
	                }
	            } // Ende von 131 ms vorbei
	        } // Ende von es wurde ein Telegramm empfangen
}
