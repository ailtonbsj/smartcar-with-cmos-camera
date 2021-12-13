/* ###################################################################
**     Filename    : main.c
**     Project     : CamNtscUsingDma
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-04, 15:20, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CamHSync.h"
#include "ExtIntLdd1.h"
#include "CamVSync.h"
#include "ExtIntLdd2.h"
#include "CamSerial.h"
#include "ASerialLdd1.h"
#include "CamADC.h"
#include "CamDMA.h"
#include "DMA1.h"
#include "TracaoEnable.h"
#include "BitIoLdd1.h"
#include "TracaoA1.h"
#include "BitIoLdd2.h"
#include "TracaoA2.h"
#include "BitIoLdd3.h"
#include "TracaoB1.h"
#include "BitIoLdd4.h"
#include "TracaoB2.h"
#include "BitIoLdd5.h"
#include "Botao1.h"
#include "BitIoLdd6.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <extras/extras_stdlib.h>

#include "dados.h"

uint8_t frameBuffer1[HEIGHT][WIDTH] = {};
char FrameFlag;
char saltoEmY;
char indiceY;

void wait(long a) {
	while (a > 0) {
		a--;
	}
}

short int cursorX = 0, cursorY = 0;

void putSerial(int valor, char charFinal, long tempoWai) {
	char result[15];
	int i;
	itoa(valor, result, 10);
	i = 0;
	while (result[i] != '\0') {
		wait(tempoWai);
		CamSerial_SendChar(result[i]);
		i++;
	}
	wait(tempoWai);
	CamSerial_SendChar(charFinal);
	wait(tempoWai);
}
int waitTime = 5555;//3500;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  unsigned long totalDeQuadros = 0;
  //double mytimer;
  
  unsigned long instrucoes = 0;
  int quantLinhas = 0;
  
  CamVSync_Disable();
  CamHSync_Disable();
  FrameFlag = FALSE;
  saltoEmY = 2;
  indiceY = 0;
  CamVSync_Enable();
  for(;;){
	  if(FrameFlag){
		  FrameFlag = FALSE;
		  indiceY = 0;
		  //Envia para Serial
		  for (cursorX = WIDTH; cursorX > 0; cursorX--) {
			  wait(waitTime);
			  CamSerial_SendChar(frameBuffer1[0][cursorX]);
		  }
		  wait(waitTime);
		  CamSerial_SendChar(250);
		  cursorY++;
		  if(cursorY > 59){
			  wait(waitTime);
			  CamSerial_SendChar(255);
			  cursorY = 0;
		  }
	   
	   
		  totalDeQuadros++;
		  /*if(mycont > 59){
			  mycont = 0;
			  mytimer++;
		  }
		  */
		  CamVSync_Enable();
	  }
	  else {
		  instrucoes++;
	  }
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

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
