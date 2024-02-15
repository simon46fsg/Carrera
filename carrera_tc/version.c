/*****************************************************************************/

/// \file       version.c
/// \author     Frank Redlich
/// \version    1.00
/// \date       15.08.2021
/// \brief      history file
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   standard oder DIY

/******************************************************************************/

#include "version.h"

#ifdef STANDARD_DECODER
    const unsigned char text_Version[] = "Standard 1.4008";
#endif

#ifdef DIY_DECODER
    const unsigned char text_Version[] = "DIY 1.4008";
#endif
    

/*******************************************************************************

 Tools:     IDE      MPLAB.X v5.50
            Compiler XC8 v2.30 (free mode)
  
neu an 1.0000
 * erste funktionierende Version
 * Bremsen sind deaktiviert

neu an 1.0001
 * Bremsen aktiviert
 * Bremslicht verk�rzt von 1,5 auf 1 s

neu an 1.0002
 * struct Spurwechseltaste umgebaut, da nicht vom Comiler / Debugger unterst�tzt
 * EEPROM Speicherstelle f�r CAR Adresse war nicht richtig initialisiert
 * das sind die Gr�nde warum das Programmieren der Autoadresse nicht
   geklappt hatte
 * Nach Programmierung der Autoadresse das Best�tigungsruckeln ge�ndert
 * Es muss 2x das gleiche Parametrierdatenwort von der CU kommen, bevor es
   ausgef�hrt wird. Nun verstellt sich die max. Geschwindigkeit nicht mehr von
   allein.
 * Ghostcarmodus hatte nicht richtig funktioniert.
 * Decodierung Programmierdatenwort von 3 auf 5 Bit erweitert

 neu an 1.0003
 * Blinken und lagsamer Fahren bei leerem Tank jetzt OK
 * Blinkfrequenz erh�ht (Tank leer und Ghostcar Geschw. Programmierung)
 * bei Fr�hstart blinkt das Auto jetzt.

 neu an 1.0004
 * neue Fahrtabelle mit Motor PWM Werten, angelehnt an den original Decoder

 neu an 1.0005
 * neue Fahrtabelle ersetzt, da Messfehler in der alten Tabelle waren. Jetzt
   sollte das Fahrverhalten identisch mit dem original Decoder sein.

 neu an 1.0006
 * wieder Fahrtabelle von Version 1.0003 eingesetzt
 * Bremslicht 0,5 statt 1 Sekunde
 * check_default_values_EEPROM(); ersetzt durch EEPROM_to_RAM();  Dadurch
   schnellere Initialisierungquit

 neu an 1.0007
 * doch wieder EEPROM_to_RAM();durch check_default_values_EEPROM(); ersetzt,
   also wieder wieder wie in Version 1.0003
 * die Spurwechseltaste muss jetzt zum Programmieren 2x innherhalb 2 Sekunden
   gedr�ckt werden
 * wenn nach Einleiten der Programmierseqeunz das Auto nach 2 Sekunden nicht
   hochgehoben wurde, dann wird die Sequenz beendet

 neu an 1.0008
 * wenn nach Einleiten der Programmierseqeunz durch 2 x dr�cken der Spurwechsel-
   taste das Auto f�hrt, dann wird die Sequenz beendet
 * neue Fahrtabelle
  
 neu an 1.1000
 * Voraussetzung: R1 von 3K3 auf 1K �ndern
 * neue Fahrtabelle 
  
 neu an 1.2000
 * Compiler von XC8 v1.12 auf XC8 v1.35 gewechselt 
 * Compiler Warnungen beseitigt
 * neues File version.c
 * Wenn Tank leer dann keine Geschwindigkeitsminderung durch Decoder mehr
 * Programmierwerte im RAM in Struktur zusammengefasst
 * Schreibbegrenzung f�r Bits von CU lesen (f�hrte zu Speicherschreibern). 
   Dadurch keine sporadischen Umprogrammierungen etc. mehr
 * nach Programmierung von Speed, Bremse und Adresse blinkt das Auto
 
 neu an 1.2001 
 * Not Aus Timeout mit Timer 0: 960 ms kein Telegramm, dann Motor aus

 neu an 1.2002 
 * minimale Pulsl�nge f�r Start von 3 ms auf 0,3 ms verk�rzt
  
 neu an 1.2003
 * EEPROM Einstellwerte werden nicht mehr im RAM gehalten sondern bei Bedarf
   immer neu gelesen
  
 neu an 1.2004
 * Formatierungen, unbenutzten Code entfernt, keine funktionielle �nderungen
 
 neu an 1.2005
 * C Compiler XC8 1.36
 * in init c war noch <htc.h> statt <xc.h> eingebunden
 * Diverse Ma�nahmen um den Datenempfang robuster zu machen
   - andere Pulsl�ngen f�r High und Low-Pulse. Durch das Schaltverhalten des
     Transistors ist die Highphase immer k�rzer als die Low Phase. Dadurch auch
     ge�nderte Auswertung im Interrupt Handler
   - da der Timer 4 f�r CCP1 und CCP2 verwendet wird, wird er jetzt in einer 
     eigenen Routine, nur einmal initialisiert
   - PWM Output Pins werden direkt nach Reset auf Eingang gestellt und erst 
     w�hrend der Initialisierung der PWM Funktion auf Ausgang 
   - es wird jetzt nur dann in den Telegramm Empfangspuffer geschrieben, wenn 
     das letzte Telegramm abgearbeitet wurde
   - wenn eine fehlerhafter Puls gemessen wurde, wird das Telegramm-Start
     Bit r�ckgesetzt   
   - nach einem Reset wird das Startbit r�ckgesetzt 
   - TEST um die H�lfte: Notaus-Timer funktion ge�ndert. Kommt nach 100 msec kein Reglertelegramm
     an, dann wird die aktuelle Fahrstufe um eins verringert.  
  
 neu an 1.2006
 * getrennte Pulsl�ngen f�r high und low Pulse wieder zur�ck ge�ndert
  
 neu an 1.3000
 * Taktfrequenz von 16MHz auf 32MHz angehoben (per Compilerswitch schaltbar), 
   dadurch schnellere Interruptabarbeitung bei Erkennen einer Flanke 
   jetzt 15�s statt 30�s 
 * Watchdog eingeschaltet
 * Zeitbasis 100s durch Telegramme z�hlen war nicht mehr genau 
   
 neu an 1.3001
 * Initialisierung der Defaultwerte im EEPROMs bei erster Inbetriebnahme wieder
   hinzu  
 * der watchdog wird erst nach der Initialisierung eingeschaltet
  
 neu an 1.3002
 * brown out enabled, high trip point
 * neuer C-Compiler XC8 v1.40
  
 neu an 1.3003
 * Fahrstufen f�r alle 16 statt bisher 10 CU Einstellungen erg�nzt 
 * Bremsstufen f�r alle 16 statt bisher 10 CU Einstellungen erg�nzt 
  
 neu an 1.4000  
 * Prozessortakt nun immer 32MHz, compilerswitch 16 MHz entfernt
 * kein Blinken mehr, wenn Einstellwerte umprogrammiert werden
 * Notaus Timer entfernt, Watchdog sollte ausreichen
 * Compilerwarnungen beseitigt (durch casting)
 * Bremswirkung unter Wert 6 werden jetzt akzeptiert 
  
 neu an 1.4001
 * Die Programmierdatenworte f�r max. Geschwindigkeit und Bremse m�ssen nur
   noch 1 x empfangen werden.   
  
 neu an 1.4002  
 * Version 1.4001 verworfen, weiter Programmierung auf Basis v. 1.4000
 * Initialisierung der clock direkt nach Programmstart
  
 neu an 1.4003  
 * per Compilerswitch standard (standard Schaltung) oder DIY Decoder (nicht 
   negierter Eingang, PWM f�r Bremslicht)
 
 neu an 1.4004  
 * jetzt auch f�r PIC16F1825, definitionen in init.c angepasst 
  
 neu an 1.4005  
 * f�r Decoder DIY2 mit getrenntem R�ck- und Bremslicht per compilerswitch
 * neuer C-Compiler XC8 v2.00
  
 neu an 1.4006  
 * Formel 1 Stopplicht 
 
 neu an 1.4007   
 * Auswertung des Aktivdatenworts
 
 neu an 1.4008  
 * Bugfix von [MiZu]:     
 * - It was possible to program car to different ID without power cycle.
 *   This worked by putting the car in ready for power cycle mode with one ID
 *   and then set the ID with another controller. Version 1.02 disregards if 
 *   there really was a power cycle. I did not change this, as there might be 
 *   timing issues to recognize power cycle or not. I made sure that the 
 *   programming and the preparing for programming is done from same 
 *   controller ID. 
 
*******************************************************************************/
