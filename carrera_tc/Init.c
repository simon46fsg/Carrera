/*****************************************************************************/

/// \file       init.c
/// \author     Frank Redlich
/// \version    1.03
/// \date       04.01.2019
/// \brief      Initialisierungsroutinen
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/

/*
 neu an 1.01 
 * compilerswitch f�r Prozessortakt entfernt, jetzt immer 32MHz  
  
 neu an 1.02 
 * init CCP4 f�r PWM R�cklicht/Bremslicht f�r DIY Decoder
  
 neu an 1.03 
 * f�r PIC16F1825 per Compilerswitch CCPTMRS statt CCPTMRS0
 */


//#include <xc.h> microchip specific stuff
#include "version.h"
#include "ports.h"
#include "typedef.h"
#include "defines.h"
#include "variable.h"
#include "eeprom.h"


#include "init.h"



/**
 * initialisiert die Peripherie des PICs
 */
void Initialisierung(void)
{


	//durch ioc ersetzen



//    //----------------------------------------- Ports auf Low stellen
//    PORTA = 0x00;
//    PORTC = 0x00;
//
//    //----------------------------------------- Ports definieren auf Eingang/Ausgang
//    // 0 == Output
//    // 1 == Input
//    // d == digital
//    // a == analog
//    // p == push pull
//    // D == open Drain
//    // R == Pullup Resistor
//
//    TRISA  = 0x2B;	      // --oi ioii
//    WPUA   = 0x20;       // --R. ....
//    ANSELA = 0x00;       // --dd dddd
//
//    //TRISC  = 0x00;	      // --oo oooo
//    TRISC  = 0x28;	      // --io iooo      nach Reset erstmal die Pins PWM Motor und Bremse als Eingang schalten
//    WPUC   = 0x00;       // --.. ....
//    ANSELC = 0x00;       // --dd dddd


    alle_Variablen_ruecksetzen();

    
    
    //durch ioc und hal funktionen ersetzen

    
//    //Init_Timer_0();                // Timeout f�r Flanken beim Datenempfang
//    Init_Timer_1();                // Zeitbasis f�r Pulsweitenmessung der CU Daten
//    //Init_Timer_2();              // Takt f�r CCP3
//    Init_Timer_4();                // Takt f�r CCP1 und CCP2
//    Init_Timer_6();                // Timeout f�r Flanken beim Datenempfang
//    Init_CCP1();                   // CCP1 f�r Motorsteuerung
//    Init_CCP2();                   // CCP2 f�r Bremse
//    Init_CCP3(IR_LED_PWM_CAR_4);   // CCP3 f�r IR LED
//    Init_CCP4();                   // CCP4 f�r Kombi-R�ck- und Bremslicht
//
//    Init_IOC_Interrupt();          // Portpin A5 Interrupts f�r Messung des CU Datensignals
//
//    WDTCONbits.WDTPS = 0b01000;    // 1:8192 (Interval 256 ms typ)
//
//    INTCONbits.PEIE = 1;           // peripheral int enable
//    INTCONbits.GIE = 1;            // Global interrupt enable
}

/******************************************************************************/



/**
 * Timer f�r Timout beim Datenempfang
 * wird sp�ter bei Startl�cke gestartet
 * wird beendet, wenn �bergelaufen 
 * 
 * �berlauf nach:
 * Fosc/4 = 32MHz/4 = 8MHz ==> 125ns
 * 125ns * 256 * 8(Prescaler) = 256us  
 */
/*
void Init_Timer_0(void)
{
    OPTION_REGbits.TMR0CS = 0;          // Internal instruction cycle clock (FOSC/4)
    OPTION_REGbits.PSA = 0;             // Prescaler is assigned to the Timer0 module
    OPTION_REGbits.PS = 0b010;          // Prescaler 1:8
    //OPTION_REGbits.PS = 0b011;          // Prescaler 1:16
    INTCONbits.TMR0IF = 0;              // clears the Timer0 interrupt flag
    //INTCONbits.TMR0IE = 1;              // Enables the Timer0 interrupt   wird bei Startl�cke gemacht
}
*/


/******************************************************************************/

/**
 * Zeitbasis zum Messen der Pulsl�ngen des Dateneingangs 
 * Takt: Fosc/4 = 16MHz/4 => 250 nsec
 *       Prescaler 4:1 ==> 1�sec
 * Takt: Fosc/4 = 32MHz/4 => 125 nsec
 *       Prescaler 8:1 ==> 1�sec 
 * �berlauf alle 65,536 ms
 */
void Init_Timer_1(void)
{
//    T1CONbits.TMR1CS = 0b00;        // timer clock is Fosc/4 = 4 MHz (16 Mhz) bzw. 8 MHz bei 32 MHz clock
//
//    T1CONbits.T1CKPS = 0b11;        // Prescaler = 8:1
//
//    PIE1bits.TMR1IE = 0;            // disble interrupt
//
//    T1CONbits.TMR1ON = 1;           // Timer 1 einschalten
}

/******************************************************************************/

/**
 * Timer 4 als Taktquelle f�r die CCP1 und CCP2 (Motor und Bremse)
 * und jetzt auchg f�r CCP4 (R�cklicht/Bremslicht f�r DIY Decoder)
 
 * * Takt: Fosc/4 = 32MHz/4 => 125 nsec
 *       Prescaler 4:1  ==> 500 nsec Takt
 
 */
void Init_Timer_4(void)
{
//    T4CONbits.TMR4ON = 1;           // Timer 4 auschalten
//
//    PR4 = 127;                      // Periodenl�nge x 500ns = 64s
//    PIR3bits.TMR4IF = 0;            // Clear the TMRxIF interrupt flag bit Timer 4
//    T4CONbits.T4CKPS = 0b01;        // Prescaler = 4:1
//
//    T4CONbits.TMR4ON = 1;           // Timer 4 einschalten
    
}


/******************************************************************************/

/**
 * Timer f�r Timout beim Datenempfang
 * wird sp�ter bei Startl�cke gestartet
 * wird beendet, wenn �bergelaufen
 * 
 * 32 MHz Fosc/4 = 4 MHz ==> 125ns Takt
 *        Prescaler 64:1 ==> 8�s Takt
 *        Postscaler 1:1 ==> Interrupt bei 26 x 8 �s = 208 �sec
 */

void Init_Timer_6(void)
{
//    T6CONbits.TMR6ON = 0;           // Timer 6 ausschalten
//    PR6 = 26;
//    TMR6 = 0;
//    T6CONbits.T6CKPS = 0b11;        // Prescaler = 64:1
//    T6CONbits.T6OUTPS = 0b0000;     // Postscaler = 1:1
}


/******************************************************************************/




/**
 * Motor
 *  
 *     PWM Period = [(PRx) + 1] * 4 * TOSC * (TMRx Prescale Value)
 *     TOSC = 1/FOSC 
 * 
 * Taktquelle ist Timer 4 (wurde vorher initialisiert)
 *     Fosc/4 = 32MHz/4 = 8MHz
 *     ==> 125ns Takt
 *     Prescaler 4:1 ==> 0,5 �s Takt
 */
void Init_CCP1(void)
{
//    TRISCbits.TRISC5 = 1;           // Disable the CCP1 pin output driver by setting the associated TRIS bit.
//
//    CCP1CONbits.CCP1M = 0b1100;     // PWM mode
//
//    CCPR1L = 0;                     // L�nge High am Ende der Periode, Motor aus
//    CCP1CONbits.DC1B = 0b00;        // 2xLSB
//
//#ifdef _16F1824
//    CCPTMRS0bits.C1TSEL = 0b01;     // Taktquelle Timer 4
//#endif
//#ifdef _16F1825
//    CCPTMRSbits.C1TSEL = 0b01;      // Taktquelle Timer 4
//#endif
//
//    TRISCbits.TRISC5 = 0;           // Enable CCP1 Pin
//
//
}

/******************************************************************************/


/**
 * Bremse
 * Taktquelle ist Timer 4
 *     Fosc/4 = 16MHz/4 = 4MHz
 *     ==> 250ns Takt
 *     Prescaler 1:1 ==> 0,25 �s Takt
 */
void Init_CCP2(void)
{
//    TRISCbits.TRISC3 = 1;           // Disable the CCP2 pin output driver by setting the associated TRIS bit.
//
//    CCP2CONbits.CCP2M = 0b1100;     // PWM mode
//
//    CCPR2L = 0;                     // L�nge High am Ende der Periode, Bremse aus
//    CCP2CONbits.DC2B = 0b00;        // 2xLSB
//
//#ifdef _16F1824
//    CCPTMRS0bits.C2TSEL = 0b01;     // Taktquelle Timer 4
//#endif
//#ifdef _16F1825
//    CCPTMRSbits.C2TSEL = 0b01;      // Taktquelle Timer 4
//#endif
//
//    TRISCbits.TRISC3 = 0;           // Enable CCP2 Pin

}

/***************************************************************************************/


/**
 * IR LED
 * Taktquelle ist Timer 2
 *     Fosc/4 = 32MHz/4 = 8MHz
 *     ==> 125ns Takt
 *     Prescaler 16:1 ==> 2�s Takt
 
 */
void Init_CCP3(U8 Periodendauer)
{
//    TRISAbits.TRISA2 = 1;           // Disable the CCP3 pin output driver by setting the associated TRIS bit.
//
//    PR2 = Periodendauer;            // Periodenl�nge x 4�s
//
//    CCP3CONbits.CCP3M = 0b1100;     // PWM mode
//
//    CCPR3L = (U8)(PR2 >> 1);        // L�nge High am Ende der Periode, duty cycle 1.1
//    CCP3CONbits.DC3B = 0b00;        // 2xLSB
//
//#ifdef _16F1824
//    CCPTMRS0bits.C3TSEL = 0b00;     // Taktquelle Timer 2
//#endif
//#ifdef _16F1825
//    CCPTMRSbits.C3TSEL = 0b00;      // Taktquelle Timer 2
//#endif
//
//
//    PIR1bits.TMR2IF = 0;            // Clear the TMRxIF interrupt flag bit Timer 2
//    T2CONbits.T2CKPS = 0b10;        // Prescaler = 16:1
//    T2CONbits.TMR2ON = 1;           // Timer 2 einschalten
//
//    TRISAbits.TRISA2 = 0;           // Enable CCP3 Pin
}


/******************************************************************************/

/**
 * Ansteuerung R�cklicht und Bremslicht
 * beim Bremsen volle Pulsl�nge ein, sonst nur 25%
 * Taktquelle ist Timer 4
 *     Fosc/4 = 16MHz/4 = 4MHz
 *     ==> 250ns Takt
 *     Prescaler 1:1 ==> 0,25 �s Takt
 */
void Init_CCP4(void)
{
//    TRISCbits.TRISC1 = 1;           // Disable the CCP4 pin output driver by setting the associated TRIS bit.
//
//    CCP4CONbits.CCP4M = 0b1100;     // PWM mode
//
//    CCPR4L = 1;                     // L�nge High am Ende der Periode, Licht aus
//    CCP4CONbits.DC4B = 0b00;        // 2xLSB
//
//#ifdef _16F1824
//    CCPTMRS0bits.C4TSEL = 0b01;     // Taktquelle Timer 4
//#endif
//#ifdef _16F1825
//    CCPTMRSbits.C4TSEL = 0b01;      // Taktquelle Timer 4
//#endif
//
//    TRISCbits.TRISC1 = 0;           // Enable CCP4 Pin

}

/******************************************************************************/

/**
 * Portpin Interrupts f�r Messung der Startl�cken einschalten
 * nur fallende Flanke
 */
void Init_IOC_Interrupt(void)
{
//    IOCANbits.IOCAN5 = 1;   // RA5 Data fallende Flanke enable
//    IOCAPbits.IOCAP5 = 1;   // RA5 Data steigende Flanke enable
//
//    INTCONbits.IOCIE = 1;   // Enable interrupt on change
} 


/******************************************************************************/             
             
/**
 * setzt alle gloabale Variable zur�ck
 */
void alle_Variablen_ruecksetzen(void)
{
    U8      Index;


    Telegramm_empfangen = NEIN;
    Licht_Sperr_Timer = 0;
    Ghostcar_Doppelklick_timeout = 0;
    Ghostcar_Doppelklick_Counter = 0;
    Bremslicht_timer = 0;
    Tank_leer_Blinken = NEIN;
    Tank_leer = NEIN;

    CU_Prg_Daten.Parameter_alt = PRG_NORMALBETRIEB;
    CU_Prg_Daten.Wert_alt = 0;

    Adr_warte_auf_Reset_timeout = 0;

    for (Index = 0; Index < MAX_REGLER; Index++)
    {
        Spurwechseltaste.Counter[Index] = 0;
        Spurwechseltaste.Letzter_Zustand[Index] = LOSGELASSEN;
    }
}

/******************************************************************************/

/**
 * pr�ft ob die Programmierwerte wie z.B. die Autoadresse schon beschrieben
 * wurden oder ob immer noch �berall FF drin steht. Wenn ja, dann werden �berall
 * Null als Defaultwerte geschrieben
 * 
 * Die Adressen EE_ADR_DEFAULT_0XAA und EE_ADR_DEFAULT_0X55 gelten als Flag ob
 * die Werte schon geschrieben wurden.
 */
void Init_EEPROM_Defaultwerte(void)
{
    U8 value;
            
    value = EE_read(EE_ADR_DEFAULT_0XAA);
    if (value != 0xAA)                        
    //if (EE_read(EE_ADR_DEFAULT_0XAA) != 0xAA)
    {
        value = EE_read(EE_ADR_DEFAULT_0X55);
        if (value != 0x55)                                
        //if (EE_read(EE_ADR_DEFAULT_0X55) != 0x55)
        {        
            EE_write_verified(0, EE_ADR_AUTO_ADRESSE);              // Auto 1 = Adresse 0            
            EE_write_verified(1, EE_ADR_LICHT);                     // Licht an
            EE_write_verified(0, EE_ADR_PROGRAMMIERMODUS);          // aus
            EE_write_verified(6, EE_ADR_BREMSWIRKUNG);              // minimale Bremswirkung
            EE_write_verified(1, EE_ADR_MAX_GESCHWINDIGKEIT);       // langsame Endgeschwindigkeit
            EE_write_verified(0, EE_ADR_GHOST_GESCHWINDIGKEIT);
            EE_write_verified(0, EE_ADR_GHOST_PROGRAMMIERMODUS);

            EE_write_verified(0xAA, EE_ADR_DEFAULT_0XAA);           // Flag, dass Default-Werte drin sind
            EE_write_verified(0x55, EE_ADR_DEFAULT_0X55);
        }
    }
}
