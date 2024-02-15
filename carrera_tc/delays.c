/*****************************************************************************/

/// \file       Delays.c
/// \author     Frank Redlich
/// \version    1.00
/// \date       08.02.2014
/// \brief      Prototypen f�rWarteschleifen
/// \details    Projekt:    Carrera_Decoder<br>
///             Prozessor:  Microchip PIC16F1824 <br>
///             Hardware:   Rev2a

/******************************************************************************/

//#include <xc.h> microchip specific stuff
#include "typedef.h"

#include "delays.h"

/**
 * kurze Warteschleife
 * ca. 100�s, C-Compiler ohne Optimierung
 */
void delay_100us (void)
{
    U8  index;

    for (index = 0; index < 30; index++)
    {
        NOP();
    }

}
