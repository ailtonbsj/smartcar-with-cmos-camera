/* ###################################################################
 **     Filename    : ProcessorExpert.c
 **     Project     : ProcessorExpert
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-03-31, 21:13, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file ProcessorExpert.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
 **  @{
 */
/* MODULE ProcessorExpert */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CamHSync.h"
#include "ExtIntLdd1.h"
#include "CamVSync.h"
#include "ExtIntLdd2.h"
#include "CamAnalog.h"
#include "Serial.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <extras/extras_stdlib.h>

#define FALLING_EDGE 0
#define RISING_EDGE 1

short int happenHori = 1, happenVert = 1;
static short int quadro[70][55];
short int cursorX = 0, cursorY = 0;
short int novoQuadro = 0;

void wait(long a) {
	while (a > 0) {
		a--;
	}
}

void putSerial(int valor, char charFinal, long tempoWai) {
	char result[15];
	int i;
	itoa(valor, result, 10);
	i = 0;
	while (result[i] != '\0') {
		wait(tempoWai);
		Serial_SendChar(result[i]);
		i++;
	}
	wait(tempoWai);
	Serial_SendChar(charFinal);
	wait(tempoWai);
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	int waitTime = 5555;//3500;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	/* For example: for(;;) { } */

	// (uint32_t) ADC0_RA
	CamAnalog_Init();

	CamHSync_Enable();
	CamVSync_Enable();

	for (;;) {
		//Captura Quadro
		novoQuadro = 0;
		cursorY = 0;
		cursorX = 0;
		while(!novoQuadro){}
		novoQuadro = 0;
		while (TRUE) {
			while (happenHori) {
			}
			while (!happenHori) {
				quadro[cursorY][cursorX] = (uint32_t) ADC0_RA;
				cursorX++;
			}
			cursorX = 0;
			cursorY++;
			while (happenHori) {
			}
			if(novoQuadro > 0) break;
			while (!happenHori) {
			}
		}
		CamHSync_Disable();
		CamVSync_Disable();
		

		//Envia para Serial
		Serial_SendChar(255);
		wait(waitTime);
		for (cursorY = 0; cursorY < 70; cursorY++) {
			for (cursorX = 0; cursorX < 55; cursorX++) {
				wait(waitTime);
				Serial_SendChar(quadro[cursorY][cursorX]);
			}
			wait(waitTime);
			Serial_SendChar(250);
		}
			
		CamHSync_Enable();
		CamVSync_Enable();
		
	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.2 [05.06]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
