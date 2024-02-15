/*****************************************************************************/

/// \file       Decoder.h
/// \author     Frank Redlich
/// \version    1.01
/// \date       11.11.2017
/// \brief      Prototypen spezieller Routinen für den Decoder
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/

/*
 neu an 1.01 
 * Notaus Timer entfernt
 */

#ifndef DECODER_H
#define	DECODER_H



void Reglerdatenwort_decodieren(void);
void Programmierdatenwort_decodieren(void);
void Parameter_verarbeiten(void);
void Count_Spurwechseltaste(U8 Adresse);
void Motor_und_Bremse_ansteuern(U8 Wert);
void Eigene_Spurwechseltaste_auswerten(void);
void Licht_schalten (void);
void Licht_einschalten (void);
void IR_LED_einschalten(void);


#endif	/* DECODER_H */

