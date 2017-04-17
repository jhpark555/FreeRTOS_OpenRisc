//--------------------------------------------------------------------------//
//----------------------- COPIED FROM AVR32 EXAMPLE ------------------------//
//--------------------------------------------------------------------------//

/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief FreeRTOS LEDs Management for AVR32 UC3.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/

/* Copyright (c) 2007, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



#include "FreeRTOS.h"
#include "task.h"
#include "partest.h"
#include "gpio.h"


/*-----------------------------------------------------------
 * Simple parallel port IO routines.
 *-----------------------------------------------------------*/

#define partstALL_OUTPUTS_OFF	( ( unsigned portCHAR ) 0x00 )
#define partstMAX_OUTPUT_LED    ( ( unsigned portCHAR ) 0x08 )

static volatile unsigned portCHAR ucCurrentOutputValue = partstALL_OUTPUTS_OFF; 

/*-----------------------------------------------------------*/

void vParTestInitialise( void )
{
	gpio_write(0, partstALL_OUTPUTS_OFF);
}
/*-----------------------------------------------------------*/

void vParTestSetLED( unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue )
{
	unsigned portCHAR ucBit;

	if( uxLED >= partstMAX_OUTPUT_LED )
	{
		return;
	}

	ucBit = ( ( unsigned portCHAR ) 1 ) << uxLED;

	vTaskSuspendAll();
	{
		if( xValue == pdTRUE )
		{
			ucCurrentOutputValue |= ucBit;
		}
		else
		{
			ucCurrentOutputValue &= ~ucBit;
		}

		gpio_write(0, ucCurrentOutputValue);
	}
	xTaskResumeAll();
}
/*-----------------------------------------------------------*/

void vParTestToggleLED( unsigned portBASE_TYPE uxLED )
{
	unsigned portCHAR ucBit;

	if( uxLED >= partstMAX_OUTPUT_LED )
	{
		return;
	}

	ucBit = ( ( unsigned portCHAR ) 1 ) << uxLED;

	vTaskSuspendAll();
	{
		ucCurrentOutputValue ^= ucBit;
		gpio_write(0, ucCurrentOutputValue);
	}
	xTaskResumeAll();
}


