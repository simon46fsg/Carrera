/*****************************************************************************/

/// \file       Handlers.c
/// \author     Frank Redlich
/// \version    1.01
/// \date       28.02.2016
/// \brief      Interrupt Service Routines 
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/
/*
 neu an 1.01 
 * durch die jetzt getrennten Pulsl�ngen f�r High und Low-Pulse, Anpassung in 
   der Auswertung der Pulse  
 */




//#include <xc.h> microchip specific stuff
#include "typedef.h"
#include "defines.h"
#include "ports.h"
#include "variable.h"


/**
 * Interrup Service Routinen
 * beim PIC16 gibt es nur einen einzigen Interrupt Vector
 * an Hand der Interrupt Flags der einzelnen Ressourcen muss abgefragt werden,
 * welcher Interrupt ausgel�st wurde
 */
//void __interrupt Handler(void) todo alles was mit interrupts zu tun hat
void placeholder()
{
    union Timer_Union   Timer1;                                                 // Timer 1 Register mit MSB und LSB

    S16                 Pulslaenge;                                             // gemessene L�nge des Pulses 
    
    U8                  Pulstyp;                                                // Art des Pulses, High, Low, L�nge

    
    
    
    
    //------------------------------------------------------------------------- Timer 0 �berlauf 
    //todo timer 0 wurde anscheinend nicht mehr genutzt
//    if (INTCONbits.TMR0IF == 1)
//    {
//        INTCONbits.TMR0IF = 0;                  // clears the Timer0 interrupt flag
        
        /*
        switch(Bitcounter)
        {
            // Aktiv Datenwort wird im Hauptprogramm nicht verwendet
            //case 8:
            //    Telegrammtyp = AKTIVDATENWORT;
            //    Telegramm_empfangen = JA;
            //    break;
            case 10:
                Telegrammtyp = REGLERDATENWORT;
                Telegramm_empfangen = JA;
                break;
            case 13:
                Telegrammtyp = PROGRAMMIERDATENWORT;
                Telegramm_empfangen = JA;
                break;
            default:                                                            // falsche Telegramml�nge
                DataBit[0] = 'X';                                               // Startbit ung�ltig machen f�r erneuten Empfang
                break;
        }

        INTCONbits.TMR0IE = 0;                  // disables the Timer0 interrupt
        INTCONbits.TMR0IF = 0;                  // clears the Timer0 interrupt flag
        TMR0 = 0;
        */ 
//    }


    //-------------------------------------------------------------------------- Timer 6 Interrupt       
//    if (PIR3bits.TMR6IF == 1)
    //todo timer 6 entry
    {
        switch(Bitcounter)
        {
            // Aktiv Datenwort wird im Hauptprogramm nicht verwendet
            //case 8:
            //    Telegrammtyp = AKTIVDATENWORT;
            //    Telegramm_empfangen = JA;
            //    break;
            case 10:
                Telegrammtyp = REGLERDATENWORT;
                Telegramm_empfangen = JA;
                break;
            case 13:
                Telegrammtyp = PROGRAMMIERDATENWORT;
                Telegramm_empfangen = JA;
                break;
            default:                                                            // falsche Telegramml�nge
                DataBit[0] = 'X';                                               // Startbit ung�ltig machen f�r erneuten Empfang
                break;
        }
//        T6CONbits.TMR6ON = 0;                                                   // Timer 6 abschalten
//        PIE3bits.TMR6IE = 0;                                                    // Interrupt wieder sperren
//        PIR3bits.TMR6IF = 0;                                                    // Interruptflag l�schen
//        TMR6 = 0;                                                               // Timer 6 r�cksetzen
    }
    

    //-------------------------------------------------------------------------- Portpin Daten Interrupt
    
//    if (IOCAFbits.IOCAF5 == 1)
//    todo timer 1 entry
    {
//        T1CONbits.TMR1ON = 0;                                                   // Timer 1 anhalten
//        Timer1.Byte.LSB = TMR1L;
//        Timer1.Byte.MSB = TMR1H;
//        T1CONbits.TMR1ON = 1;                                                   // Timer 1 einschalten
        
        Pulslaenge = Timer1.Wort - Alter_Timer_Wert;                            // Pulslaenge = Neuer_Timer_Wert - Alter_Timer_Wert;        
        Alter_Timer_Wert = Timer1.Wort;                                         // Alter_Timer_Wert = Neuer_Timer_Wert;

        
        //----------------------------------------------------------------------   ermitteln, was das f�r ein Puls war
        Pulstyp = PULS_UNBEKANNT;                                               // noch ist nicht klar was das war
        //if (Pin_i_DATA == 1)                                                    // wenn jetzt High ist, dann war es ein:  
#ifdef INPUT_INVERTED
        if (1/*Pin_i_DATA == 1*/)    //todo makro gpio                                                // wenn jetzt High ist, dann war es ein:
#else
        if (1/*Pin_i_DATA == 0*/)   //todo makro gpio                                                 // wenn jetzt Low ist, dann war es ein:
#endif
        {                                                                       // Low Puls         
            if ((Pulslaenge > LOW_PULS_KURZ_MIN) && (Pulslaenge < LOW_PULS_KURZ_MAX))  
                Pulstyp = PULS_KURZ_LOW;
            if ((Pulslaenge > LOW_PULS_LANG_MIN) && (Pulslaenge < LOW_PULS_LANG_MAX))  
                Pulstyp = PULS_LANG_LOW;
            if ((Pulslaenge > PULS_START_MIN) && (Pulslaenge < PULS_START_MAX)) // Startbit 
                Pulstyp = PULS_START;
        }
        else                                                                    // wenn jetzt Low ist, dann war es ein High Puls 
        {
            if ((Pulslaenge > HIGH_PULS_KURZ_MIN) && (Pulslaenge < HIGH_PULS_KURZ_MAX))  
                Pulstyp = PULS_KURZ_HIGH;
            if ((Pulslaenge > HIGH_PULS_LANG_MIN) && (Pulslaenge < HIGH_PULS_LANG_MAX))  
                Pulstyp = PULS_LANG_HIGH;
        }        
        
        //----------------------------------------------------------------------  Auswertung je nach Puls 
        if (Telegramm_empfangen == NEIN)                                        // nur in den Empfagspuffer schreiben, wenn das letzte   
        {                                                                       // Telegramm schon abgeholt wurde      
            switch (Pulstyp)                                                        
            {
                case PULS_START:

                    Bitmitte = NEIN;
                    DataBit[0] = 'S';
                    Bitcounter = 1;


                    //todo warum wird hier was mit timer 6 gemacht? timeout zurücksetzen?
//                    T6CONbits.TMR6ON = 0;                                       // Timer 6 ist schon abschaltet
//                    TMR6 = 0;                                                   // Timer 6 r�cksetzen
//                    PIR3bits.TMR6IF = 0;                                        // Interrupt Flag r�cksetzen
//                    PIE3bits.TMR6IE = 1;                                        // Interrupt wieder erlauben
                
//                    T6CONbits.TMR6ON = 1;                                       // Timer 6 einschalten

                    /*                    
                    NOP();
                    TMR0 = 0;                           // Timer 0 r�cksetzen
                    INTCONbits.TMR0IF = 0;              // clears the Timer0 interrupt flag
                    INTCONbits.TMR0IE = 1;              // Enables the Timer0 interrupt                            
                    NOP();
                    */ 
                    
                    break;

                case PULS_KURZ_HIGH:
                case PULS_KURZ_LOW:
                
                    if (DataBit[0] == 'S')                                      // wenn die Startl�cke da war
                    {   
                        if (Bitmitte == NEIN)                                   // ein kurzer Puls k�nnte die Bit-Mitte sein
                        {                                                       // oder das Bit-Ende 
                            Bitmitte = JA;
//                            TMR6 = 0;  todo timer 6 zurücksetzen                                         // Timer 6 r�cksetzen
                            //TMR0 = 0;                                           // Timer 0 r�cksetzen
                        }
                        else
                        {
                            Bitmitte = NEIN;
                            if (Pulstyp == PULS_KURZ_LOW)
                                DataBit[Bitcounter] = 1;
                            else
                                DataBit[Bitcounter] = 0;
                    
                            if (Bitcounter < (MAX_DATABITS - 1))                            
                                Bitcounter++;

                            //TMR0 = 0;                 // Timer 0 r�cksetzen
                            //TMR6 = 0;  todo timer 6 zurück setzen                                         // Timer 6 r�cksetzen
                        }            
                    }            
                    break;
                
                
                case PULS_LANG_HIGH:
                case PULS_LANG_LOW:
                
                    if (DataBit[0] == 'S')                                      // wenn die Startl�cke da war
                    {
                        Bitmitte = NEIN;
                    
                        if (Pulstyp == PULS_LANG_LOW)
                            DataBit[Bitcounter] = 1;
                        else
                            DataBit[Bitcounter] = 0;

                        if (Bitcounter < (MAX_DATABITS - 1))                            
                            Bitcounter++;

                        //TMR0 = 0;                 // Timer 0 r�cksetzen
//                        TMR6 = 0; todo timer 6 zurück setzen                                               // Timer 6 r�cksetzen
                    }
                    break;
                
                default:                                                        // unbekannte Pulsl�nge / Fehler
                    DataBit[0] = 'X';                                           // Startbit ung�ltig machen f�r erneutemn Empfang
                                        
                    break;
            } // Ende switch Pulstyp
        } // Ende das letzte Telegramm wurde schon im Hauptprogramm verarbeitet
        
//        IOCAFbits.IOCAF5 = 0;                                                   // Interrupt Flag wieder l�schen
    }
      
    

}

