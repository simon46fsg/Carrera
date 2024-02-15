/*****************************************************************************/

/// \file       ports.h
/// \author     Frank Redlich
/// \version    1.01
/// \date       30.12.2017
/// \brief      Portpin definitions
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   standard oder DIY

/******************************************************************************/
/*
 neu an 1.01 
 * Pin RC1 als PWM output f�r R�cklicht/Bremse CCP4
 */



#ifndef PORTS_H
#define PORTS_H

//#include <xc.h> microchip specific stuff

//todo look here for the makro port stuff


/**************************************************************************************************/
/*                                      Ports                                                     */
/**************************************************************************************************/

//                                                  //  DIL QFN
//#define 	Port_Name_A		    PORTA

//#define 	Pin_Name_A0     	PORTAbits.RA0	    //  13  12  Emulator/Programmer Data	in
//#define 	Pin_Name_A1 		PORTAbits.RA1		//  12  11  Emulator/Programmer Clock   in
//#define 	Pin_o_IR_LED        PORTAbits.RA2		//  11  10  IR LED �ber PWM CCP3        out
//#define 	Pin_Name_A3		    PORTAbits.RA3		//  04  03  Master clear                in
//#define	Pin_Name_A4		    PORTAbits.RA4		//  03  02  n.c.                        out
//#define     Pin_i_DATA          PORTAbits.RA5		//  02  01  Daten von CU                in + Pullup


//#define 	Port_Name_C         PORTC
//#define 	Pin_o_LICHT         PORTCbits.RC0       //  10  09  Scheinwerfer und R�cklicht  out
//#define 	Pin_o_PWM_LICHT     PORTCbits.RC1		//  09  08  PWM R�cklicht/Bremslicht    out
//#define 	Pin_o_BREMSLICHT    PORTCbits.RC2		//  08  07  Bremslicht                  out
//#define 	Pin_o_BREMSE        PORTCbits.RC3		//  07  06  Bremse �ber PWM CCP2        out
//#define	Pin_Name_C4		    PORTCbits.RC4		//  06  05  n.c.                        out
//#define     Pin_o_MOTOR         PORTCbits.RC5		//  05  04  Motor  �ber PWM CCP1        out






#endif // PORTS_H 
	
