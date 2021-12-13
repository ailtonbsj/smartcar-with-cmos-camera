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
#include <stdlib.h>
#include <extras/extras_stdlib.h>

#include "dados.h"

//Cam RCA
uint8_t frameBuffer1[HEIGHT][WIDTH] = { };
char frameFlag;
char saltoEmY;
char indiceY;

//Processing Cam
unsigned char thrY = 0;
unsigned char maiorAmostra = 0;
unsigned char menorAmostra = 255;
unsigned char auX;
unsigned char deltaAmostra = 0;
unsigned char limiar;
uint8_t frameLine[HEIGHT][WIDTH_REAL] = { };
signed char bordaL, bordaR, auX_s, auY_s;
signed char diffBorda = 0;
unsigned char isSignal = FALSE;
signed char ladoL, ladoR;
signed char signalFeedback = 0;
signed char signalError = 0;
signed char signalErrorAbs = 0;
signed char signalControlServo = 0;
signed char signalControlTracao = 0;
int servo;
signed long motor1, motor2;
unsigned char ativaParada = FALSE;

#define RETA 1
#define CURVA 0
char typeTrack = 0;
char contaCurvas = 0;
char contRetas = 0;
char contaFreio = 0;
char isBoost = 0;
char isFreio = 0;

//Tracao
int maxTracao = 1;//1
int minTracao = 900;//900

unsigned int RETA_MAX = 1;
unsigned int RETA_MIN = 600;
unsigned int CURVA_MAX = 1;
unsigned int CURVA_MIN = 600;
unsigned int FREIO_MAX = 1;
unsigned int FREIO_MIN = 600;

//Funções
void setServo(int16 giro) {
	if (giro < ESQUERDA_SERVO) {
		giro = ESQUERDA_SERVO;
	}
	if (giro > DIREITO_SERVO) {
		giro = DIREITO_SERVO;
	}
	Servo_SetDutyUS(giro);
}

void setTracao(signed long motor1, int16 motor2) {
	if (motor1 < 1) motor1 = 1;
	else if (motor1 > 999) motor1 = 999;
	if (motor2 < 1) motor2 = 1;
	else if (motor2 > 999)	motor2 = 999;
	TracaoA1_SetDutyUS(motor1);
	TracaoB1_SetDutyUS(motor2);
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

#define ONESEG 5000000 // ~ 1.04 segundos
void wait(long a) {
	while (a > 0) {
		a--;
	}
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
	
	//Inicializando modulos
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
	Relogio1_Enable();
	
	for(;;){
		//Processa Linha ja capturada!
		if( (thrY < indiceY) && (thrY <= LINEBOOST) ){
			//Binariza linha
			maiorAmostra = 0;
			menorAmostra = 255;
			for (auX = MINCAM; auX < MAXCAM; auX++) {
				if (maiorAmostra < frameBuffer1[thrY][auX]) maiorAmostra = frameBuffer1[thrY][auX];
				if (menorAmostra > frameBuffer1[thrY][auX]) menorAmostra = frameBuffer1[thrY][auX];
			}
			deltaAmostra = maiorAmostra - menorAmostra;
			
			if(deltaAmostra > DELTAAMOSTRA_MIN) limiar = ((float) deltaAmostra / 2) + menorAmostra + 3;
			else limiar = LIMIAR_PADRAO;
			
			for (auX = MINCAM; auX < MAXCAM; auX++) {
				frameLine[thrY][auX - MINCAM] = frameBuffer1[thrY][auX] > limiar;
			}
			
			//Controle do SERVO
			if(thrY == LINENOW){
				bordaL = -1;
				bordaR = -1;
				for (auX_s = CENTCAML; auX_s >= 0; auX_s--) {
					if (!frameLine[thrY][auX_s]) {
						bordaL = auX_s;
						break;
					}
				}
				for (auY_s = CENTCAMR; auY_s < WIDTH_REAL; auY_s++) {
					if (!frameLine[thrY][auY_s]) {
						bordaR = auY_s;
						break;
					}
				}
				
				diffBorda = 0;
				isSignal = FALSE;
				if(deltaAmostra > DELTA_AMOSTRA_MIN){
					if((bordaL != -1) && (bordaR != -1)){
						//Tenta achar duas linhas
						diffBorda = bordaR - bordaL;
						if((diffBorda > (WIDTH_TRACK-WIDTH_TRACK_RANGE)) && (diffBorda < (WIDTH_TRACK+WIDTH_TRACK_RANGE))){
							isSignal = TRUE;
						}
					}
					else if((bordaL != -1) || (bordaR != -1)){
						//Tenta achar uma linha
						isSignal = TRUE;
					}
				}
				
				if(isSignal){
					if (bordaL == -1) {
						ladoL = bordaR - WIDTH_TRACK;
						ladoR = bordaR;
					} else if (bordaR == -1) {
						ladoL = bordaL;
						ladoR = bordaL + WIDTH_TRACK;
					} else {
						ladoR = bordaR;
						ladoL = bordaL;
					}
					signalFeedback = (ladoR + ladoL) / 2;
					signalError = REFERENCE - signalFeedback;
					signalErrorAbs = abs(signalError);
				}
				else {
					if(signalErrorAbs > SATURARERROIN) signalError = 2*(signalError/signalErrorAbs)*MIN_ERRO;
				}
				
				#define KpMinTracao 1
				#define KpMaxTracao 2
				
				signalControlServo = signalError;
				//#0.037 0.04 0.05   *abs(signalError)
				signalControlTracao = signalError;
				//signalControlTracao = (KpMinTracao + (KpMaxTracao - KpMinTracao)*((float) (signalErrorAbs-MIN_ERRO)/MIN_ERRO)) * signalError;
				
				servo = ESQUERDA_SERVO	+ (DIREITO_SERVO - ESQUERDA_SERVO)*((float)(signalControlServo - MIN_ERRO)/RANGE_ERRO);
				setServo(servo);
				
				motor2 = maxTracao + (minTracao-maxTracao)*((float) (signalControlTracao)/(MAX_ERRO));
				motor1 = minTracao + (maxTracao-minTracao)*((float) (signalControlTracao-MIN_ERRO)/(-MIN_ERRO));
				
				setTracao(motor1, motor2);
			}
			
			//Controle do Boost e EndLine
			if(thrY == LINEBOOST){
				//Boost
				bordaL = -1;
				bordaR = -1;
				for (auX_s = CENTCAML; auX_s >= LIMBOOSTL; auX_s--) {
					if (!frameLine[thrY][auX_s]) {
						bordaL = auX_s;
						break;
					}
				}
				for (auY_s = CENTCAMR; auY_s < LIMBOOSTR; auY_s++) {
					if (!frameLine[thrY][auY_s]) {
						bordaR = auY_s;
						break;
					}
				}
				
				diffBorda = 0;
				if(deltaAmostra > DELTA_AMOSTRA_MIN){
					if((bordaL != -1) && (bordaR != -1)){
						//Tenta achar duas linhas
						diffBorda = bordaR - bordaL;
						if(diffBorda > WIDTH_BOOST_TRACK) typeTrack = RETA;
						else typeTrack = CURVA;
					}
					else if((bordaL == -1) && (bordaR == -1) && (typeTrack == RETA)) typeTrack = RETA;
					else typeTrack = CURVA;
				}
				else typeTrack = CURVA;
				
				if(typeTrack){
					//RETA
					contRetas++;
					if(contRetas > NUMBER_RETAS){
						acenderLeds(0b1111);
						maxTracao = RETA_MAX;
						minTracao = RETA_MIN;
						isBoost = TRUE;
						contaCurvas = 0;
						contaFreio = 0;
						contRetas = NUMBER_RETAS+1;
					}
				}
				else {
					//CURVA
					if(isBoost){
						contaCurvas++;
						if(contaCurvas > NUMBER_CURVAS){
							maxTracao = FREIO_MAX;
							minTracao = FREIO_MIN;
							isBoost = FALSE;
							isFreio = TRUE;
							contRetas = 0;
							contaFreio = 0;
							acenderLeds(0b0000);
						}					
					}
					else {
						if(isFreio){
							contaFreio++;
							if(contaFreio > CICLOS_FREIO) isFreio = FALSE; //Controla o tempo do Freio
						}
						else {
							maxTracao = CURVA_MAX;
							minTracao = CURVA_MIN;
						}
					}
				}
				
				//EndLine
				unsigned char vy, vx;
				unsigned char contPad = 0;
				unsigned char padFinded = 0;
				for(vy = 0; vy < 8; vy++){
					for(vx = 2; vx < 67; vx++){
						if(contPad == 0){
							if( (!frameLine[vy][vx]) && (frameLine[vy][vx-1]) && (frameLine[vy+1][vx]) && (frameLine[vy+1][vx-1]) ) contPad++;
						}
						else if(contPad > 0){
							if( ((!frameLine[vy][vx]) && (frameLine[vy+1][vx])) || ((frameLine[vy][vx]) && (!frameLine[vy+1][vx])) ) contPad++;
							else if( (frameLine[vy][vx]) && (frameLine[vy+1][vx]) ) {
								if(contPad > 2) padFinded += contPad;
								contPad = 0;
							}
							else contPad = 0;
						}
					}
				}
				
				if( (padFinded < 11) || (padFinded > 25) || (signalErrorAbs > RANGEATIVOERRO) ) padFinded = 0;
				
				if( (padFinded > 19) && ativaParada ){
					//STOP CAR
					RETA_MAX = 999;
					RETA_MIN = 999;
					CURVA_MAX = 999;
					CURVA_MIN = 999;
					FREIO_MAX = 999;
					FREIO_MIN = 999;
				}
				
			}
			
			thrY++;
		}
		
		//Novo Quadro Capturado!
		if (frameFlag) {
			frameFlag = FALSE;
			indiceY = 0;
			thrY = 0;
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
