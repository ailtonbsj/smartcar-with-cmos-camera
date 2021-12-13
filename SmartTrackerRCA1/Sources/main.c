/* ###################################################################
 **     Filename    : main.c
 **     Project     : SmartTrackerRCA1
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-06-26, 00:14, # CodeGen: 0
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
#include "CamADC.h"
#include "CamDMA.h"
#include "DMA1.h"
#include "Servo.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "LED1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "BitIoLdd3.h"
#include "LED4.h"
#include "BitIoLdd4.h"
#include "TracaoA1.h"
#include "PwmLdd2.h"
#include "TU2.h"
#include "TracaoA2.h"
#include "PwmLdd3.h"
#include "TracaoEnable.h"
#include "BitIoLdd5.h"
#include "TracaoB1.h"
#include "PwmLdd4.h"
#include "TracaoB2.h"
#include "PwmLdd5.h"
#include "Relogio1.h"
#include "TimerIntLdd1.h"
#include "TU3.h"
#include "SW1.h"
#include "BitIoLdd6.h"
#include "SW2.h"
#include "BitIoLdd7.h"
#include "SW3.h"
#include "BitIoLdd8.h"
#include "SW4.h"
#include "BitIoLdd9.h"
#include "WDog1.h"
#include "Serial1.h"
#include "ASerialLdd1.h"
#include "Botao1.h"
#include "BitIoLdd10.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "dados.h"
#include <stdlib.h>

//Cam RCA
uint8_t frameBuffer1[HEIGHT][WIDTH] = { };
uint8_t frameLine[MAXCAM - MINCAM] = { };
char frameFlag;
char saltoEmY;
char indiceY;

//Processing Cam
unsigned char maiorAmostra = 0;
unsigned char menorAmostra = 255;
unsigned char auX;
unsigned char deltaAmostra = 0;
unsigned char limiar;
//signed char auX_s, auY_s, bordaL, bordaR, ladoL, ladoR;
//signed char diffBorda = 0;
//unsigned char widthTrack = WIDTH_TRACK;
//unsigned char quantLinhas = 2;
//unsigned char quantLinhasPrevious = 2;
//unsigned char ladoReal;
//signed char output = 0;
//signed char err = 0, errAbs = 0;
//int servo, motor1, motor2;
//char contTrack = 0;
//signed char previousErr = 0, previousErrAbs = 0;
//float Kp = 1.0;

//debug
//long contaQuadros = 0;

void wait(long a) {
	while (a > 0) {
		a--;
	}
}

void setServo(int16 giro) {
	if (giro < ESQUERDA_SERVO) {
		giro = ESQUERDA_SERVO;
	}
	if (giro > DIREITO_SERVO) {
		giro = DIREITO_SERVO;
	}
	Servo_SetDutyUS(giro);
}

int acenderLeds(uint8 num) {
	if (num & 1)
		LED1_PutVal(TRUE);
	else
		LED1_PutVal(FALSE);
	if (num & 2)
		LED2_PutVal(TRUE);
	else
		LED2_PutVal(FALSE);
	if (num & 4)
		LED3_PutVal(TRUE);
	else
		LED3_PutVal(FALSE);
	if (num & 8)
		LED4_PutVal(TRUE);
	else
		LED4_PutVal(FALSE);
	return 0;
}

void setTracao(int16 motor1, int16 motor2) {
	if (motor1 < MAX_PWM_MOTOR) motor1 = MAX_PWM_MOTOR;
	if (motor1 > MIN_PWM_MOTOR) motor1 = MIN_PWM_MOTOR;
	if (motor2 < MAX_PWM_MOTOR) motor2 = MAX_PWM_MOTOR;
	if (motor2 > MIN_PWM_MOTOR)	motor2 = MIN_PWM_MOTOR;
	TracaoA1_SetDutyUS(motor1);
	TracaoB1_SetDutyUS(motor2);
}

int captaValueSwitch() {
	int saida = 0;
	if (SW1_GetVal()) {
		saida = saida | 1;
	}
	if (SW2_GetVal()) {
		saida = saida | 2;
	}
	if (SW3_GetVal()) {
		saida = saida | 4;
	}
	if (SW4_GetVal()) {
		saida = saida | 8;
	}
	return saida;
}

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
	CamVSync_Disable();
	CamHSync_Disable();
	frameFlag = FALSE;
	saltoEmY = 2;
	indiceY = 0;
	CamVSync_Enable();
	setServo(CENTRO_SERVO);
	
	TracaoEnable_PutVal(TRUE);
	TracaoA2_SetDutyUS(999);
	TracaoB2_SetDutyUS(999);
	TracaoA1_SetDutyUS(999);
	TracaoB1_SetDutyUS(999);
	
	//Kp = 0.5 + 2.5*((float) captaValueSwitch()/15);
	
	while(!Botao1_GetVal()){
	}
	(void)WDog1_Init(NULL);
	
	for (;;) {
		//Linha 6 capturada!
		if(indiceY > LINENOW && indiceY < LINENOW+2){
			maiorAmostra = 0;
			menorAmostra = 255;
			for (auX = MINCAM; auX < MAXCAM; auX++) {
				if (maiorAmostra < frameBuffer1[LINENOW][auX]) maiorAmostra = frameBuffer1[LINENOW][auX];
				if (menorAmostra > frameBuffer1[LINENOW][auX]) menorAmostra = frameBuffer1[LINENOW][auX];
			}
			deltaAmostra = maiorAmostra - menorAmostra;
			limiar = ((float) deltaAmostra / 2) + menorAmostra + 3;
			for (auX = MINCAM; auX < MAXCAM; auX++) {
				frameLine[auX - MINCAM] = frameBuffer1[LINENOW][auX] > limiar;
			}
//			
//			bordaL = -1;
//			bordaR = -1;
//			if(deltaAmostra > DELTA_AMOSTRA_MIN){
//				for (auX_s = CENTCAML; auX_s > 0; auX_s--) {
//					if (frameLine[auX_s] != frameLine[auX_s-1]) {
//						bordaL = auX_s;
//						break;
//					}
//				}
//				for (auY_s = CENTCAML; auY_s < (WIDTH_REAL-1); auY_s++) {
//					if (frameLine[auY_s] != frameLine[auY_s+1]) {
//						bordaR = auY_s;
//						break;
//					}
//				}
//			}
//			
//			diffBorda = 0;
//			if(bordaL != -1 && bordaR != -1) diffBorda = bordaR - bordaL;
//			if(diffBorda && (diffBorda < WIDTH_TRACK/2)) bordaR = -1;
//			
//			for (auX_s = CENTCAML; auX_s >= 0; auX_s--) {
//				if (!frameLine[auX_s]) {
//					bordaL = auX_s;
//					break;
//				}
//			}
//			
//			for (auY_s = CENTCAMR; auY_s < WIDTH_REAL; auY_s++) {
//				if (!frameLine[auY_s]) {
//					bordaR = auY_s;
//					break;
//				}
//			}
//			
//			// FOR DEBUG - FIND THE CENTER OF DE CAR AND CAMERA     BEGIN
//			char leds = abs((CENTCAML - auX_s) - (auY_s - CENTCAMR));
//			if (leds == 0) acenderLeds(0b1111);
//			else if (leds == 1) acenderLeds(0b1110);
//			else if (leds == 2)	acenderLeds(0b1100);
//			else if (leds == 3) acenderLeds(0b1000);
//			else acenderLeds(0);
//			// FOR DEBUG - FIND THE CENTER OF DE CAR AND CAMERA     END
//			
//			//FOR DEBUG - HAS TWO LINES BEGIN
//			if(bordaL == 0 || bordaR == WIDTH_REAL) acenderLeds(0b0000);
//			else acenderLeds(0b1111);
//			//FOR DEBUG - HAS TWO LINES END
//			
//			//Find distance between two border auto
//			if (contTrack < 15) {
//				contTrack++;
//				if (contTrack == 15) {
//					widthTrack = diffBorda;
//				}
//			}
//
//			if (bordaL == 0) {
//				ladoL = bordaR - widthTrack;
//				ladoR = bordaR;
//			} else if (bordaR == WIDTH_REAL) {
//				ladoL = bordaL;
//				ladoR = bordaL + widthTrack;
//			} else {
//				ladoR = bordaR;
//				ladoL = bordaL;
//			}
//			
//			#define LADO_L 1
//			#define LADO_R 0
//			
//			if(deltaAmostra > DELTA_AMOSTRA_MIN){
//				if((bordaL != -1) && (bordaR != -1)){ //&& (diffBorda > 40)
//					quantLinhas = 2;
//				}
//				else if((bordaL != -1) || (bordaR != -1)) quantLinhas = 1;
//			} else quantLinhas = 0;
//			
//			if((quantLinhasPrevious == 2) && (quantLinhas == 1)){
//				if(bordaL != -1) ladoReal = LADO_L;
//				else ladoReal = LADO_R;
//			}
//			if(quantLinhas == 1){
//				if(ladoReal){ //LADO L
//					if(bordaL != -1) ladoL = bordaL;
//					else ladoL = bordaR;
//					ladoR = ladoL + widthTrack;
//				}
//				else { //LADO R
//					if(bordaL != -1) ladoR = bordaL;
//					else ladoR = bordaR;
//					ladoL = ladoR - widthTrack;
//				}
//			}
//			else if(quantLinhas == 2){
//				ladoL = bordaL;
//				ladoR = bordaR;
//			}
//			quantLinhasPrevious = quantLinhas;
//		
//			output = (ladoR + ladoL) / 2;
//			err = CENTCAML - output;
//			
//			Serial1_SendChar(err+128);
//			
//			err = ((float) KP*err);
//			//errAbs = abs(err);
//			
//			
//			
//			
//			servo = ESQUERDA_SERVO	+ (DIREITO_SERVO - ESQUERDA_SERVO)*((float)(err - MIN_ERRO)/RANGE_ERRO);
//			setServo(servo);
//			
//			motor1 = REG_TRACAO;
//			motor2 = REG_TRACAO;
//			setTracao(motor1, motor2);
//			
//			//Serial1_SendChar(err+128);
//	
//			if (previousErrAbs > TRAVA_ATIVO) { //Trava o carro para caso perder pista, voltar
//				//if (diffBorda > MIN_DESTRAVA && diffBorda < MAX_DESTRAVA && ((previousErr > 0 && err > 0) || (previousErr < 0 && err < 0))) {
//				if ((diffBorda > MIN_DESTRAVA) && (diffBorda < MAX_DESTRAVA)) {
//					
//				} else {
//					err = previousErr;
//					errAbs = previousErrAbs;
//				}
//			}
//			servo = ESQUERDA_SERVO	+ (DIREITO_SERVO - ESQUERDA_SERVO)*((float)(err - MIN_ERRO)/RANGE_ERRO);
//			setServo(servo);
//			setServo(CENTRO_SERVO);
//	
//			if (diffBorda > 75 && previousErrAbs < 19) {
//				err = previousErr;
//				errAbs = previousErrAbs;
//				setServo(CENTRO_SERVO);
//			} else {
//				servo = ESQUERDA_SERVO	+ (DIREITO_SERVO - ESQUERDA_SERVO)*((float)(err - MIN_ERRO)/RANGE_ERRO);
//				setServo(servo);
//			}
//			
//			if(errAbs > DIFERENCIAL_ATIVO){
////				int y1 = REG_TRACAO + (MIN_TRACAO - REG_TRACAO)*((float)(errAbs - 15)/(30-15));
////				int y2 = REG_TRACAO + (MAX_TRACAO - REG_TRACAO)*((float)(errAbs - 15)/(30-15));
//				int y1 = MAX_TRACAO + (MIN_TRACAO - MAX_TRACAO)*((float)(errAbs - DIFERENCIAL_ATIVO)/(MIN_ERRO-DIFERENCIAL_ATIVO));
//				int y2 = MIN_TRACAO + (MAX_TRACAO - MIN_TRACAO)*((float)(errAbs - DIFERENCIAL_ATIVO)/(MIN_ERRO-DIFERENCIAL_ATIVO));
//				//int y1 = MAX_TRACAO;
//				//int y2 = MIN_TRACAO;
//				if(err > 0) motor1 = y2, motor2 = y1;
//				else motor1 = y1, motor2 = y2;
//			}
//			else {
//				motor1 = REG_TRACAO;
//				motor2 = REG_TRACAO;
//			}
//			setTracao(motor1, motor2);
//			//setTracao(motor1, motor2);
//			
//			Serial1_SendChar(err + 100);
//			
//			previousErr = err;
//			previousErrAbs = errAbs;
		}
		
		//Novo Quadro Capturado!
		if (frameFlag) {
			frameFlag = FALSE;
			indiceY = 0;
			(void)WDog1_Clear(NULL);
			//Serial1_SendChar('\n');
			CamVSync_Enable();
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
