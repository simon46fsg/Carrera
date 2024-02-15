/*****************************************************************************/

/// \file       version.h
/// \author     Frank Redlich
/// \version    1.04
/// \date       26.12.2020
/// \brief      history file
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 / PIC16F1825 <br>
///             Hardware:   DIY oder standard Decoder

/******************************************************************************/

/*
 neu an 1.01 
 * compilerswitch für standard bzw. DIY Decoder 
  
neu an 1.02 
 * compilerswitch für DIY Standard Decoder mit #undef 

neu an 1.03 
 * compilerswitch für DIY2 Decoder mit getrenntem Rück-und Bremslicht 

neu an 1.04 
 * Formel 1 Bremslicht 
  
*/ 

#undef  STANDARD_DECODER
#define DIY_DECODER

#undef  KOMBI_LEUCHTEN
#define SEPARATE_LEUCHTEN

#undef FORMEL_1_BREMSLICHT



 extern const unsigned char text_Version[];
