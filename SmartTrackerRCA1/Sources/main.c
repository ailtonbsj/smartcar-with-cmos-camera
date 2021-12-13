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

#include "dados.h"
#include <stdlib.h>
#include <extras/extras_stdlib.h>

//Tracao
int MAX_TRACAO = 1;
int MIN_TRACAO = 900;
#define RANGE_TRACAO (MAX_TRACAO-MIN_TRACAO)

//Processing
unsigned char WIDTH_TRACK = 64;
unsigned char WIDTH_TRACK_RANGE = 10;
unsigned char DELTA_AMOSTRA_MIN = 47; //47

//Cam RCA
uint8_t frameBuffer1[HEIGHT][WIDTH] = { };
uint8_t frameLine[WIDTH_REAL] = { };
uint8_t frameLineBoost[WIDTH_REALBOOST] = { };

char frameFlag;
char saltoEmY;
char indiceY;

//Processing Cam
unsigned char maiorAmostra = 0;
unsigned char menorAmostra = 255;
unsigned char maiorAmostraBoost = 0;
unsigned char menorAmostraBoost = 255;
unsigned char auX, auXBoost;
unsigned char deltaAmostra = 0;
unsigned char deltaAmostraBoost = 0;
unsigned char limiar, limiarBoost;
signed char bordaL, bordaR, auX_s, auY_s, bordaLBoost, bordaRBoost;
signed char diffBorda = 0;
signed char diffBordaBoost = 0;
unsigned char isSignal = FALSE;
signed char ladoL, ladoR;
signed char signalFeedback = 0;
signed char signalError = 0;
signed char signalErrorAbs = 0;
signed char signalControlServo = 0;
signed char signalControlTracao = 0;
int servo;
signed long motor1, motor2;

#define RETA 1
#define CURVA 0
char typeTrack = 0;
char contaCurvas = 0;
char contRetas = 0;
char contaFreio = 0;
char isBoost = 0;
char isFreio = 0;

//debug
//unsigned char *signalUART;
//unsigned char ajusteUART;
//int v;
//long contaQuadros = 0;

void wait(long a) {
	while (a > 0) {
		a--;
		//(void)WDog1_Clear(NULL);
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

void setTracao(signed long motor1, int16 motor2) {
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

void enviaChar(char lt, long tm){
	Serial1_SendChar(lt);
	wait(tm);
}

void enviaString(char st[], long tm, char nl){
	char *s;
	s = st;
	while(*s){
		enviaChar(*s, tm);
		s++;
	}
	if(nl){
		enviaChar('\r',tm);
		enviaChar('\n',tm);
	}
}

void enviaVariavel(char strName[], int vari, long tm){
	char confStr[15];
	enviaString(strName, tm, FALSE);
	itoa(vari, confStr, 10);
	enviaString(confStr, tm, TRUE);
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
	//(void)WDog1_Init(NULL);
	
	//debug
//	signalUART = &signalError;
//	ajusteUART = 100;
	
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
	
//	////////////BLUE INICIO ////////////
//	
//	while(!Botao1_GetVal()){
//		//(void)WDog1_Clear(NULL);
//	}
//	
//	long tm = 5000;//500
//	
//	enviaString("MODO CONFIGURAR (by Ailton)", tm, TRUE);
//	enviaString(" ", tm, TRUE);
//	
//	enviaVariavel("[01] REG_TRACAO ", MAX_TRACAO, tm);
//	enviaVariavel("(02) LINENOW ", LINENOW, tm);
//	enviaVariavel("[03] WIDTH_TRACK ", WIDTH_TRACK, tm);
//	enviaVariavel("[04] WIDTH_TRACK_RANGE ", WIDTH_TRACK_RANGE, tm);
//	enviaVariavel("[05] DELTA_AMOSTRA_MIN ", DELTA_AMOSTRA_MIN, tm);
//	enviaVariavel("(06) MIN_ERRO ", MIN_ERRO, tm);
//	enviaVariavel("(07) CENTRO_SERVO ", CENTRO_SERVO, tm);
//	enviaVariavel("(08) LIBERDADE_SERVO ", LIBERDADE_SERVO, tm);
//	enviaString("[12] SinalUART = 01 deltaAmostra, 02 limiar, 03 bordaL, 04 bordaR, 05 diffBorda, 06 signalFeedback, 07 signalError, 08 signalControl_st, 09 signalControl_tr", tm, TRUE);
//	enviaString("(99) <- Iniciar!!!", tm, TRUE);
//	
//	enviaString(" ", tm, TRUE);
//	enviaString("Esperando comando ou acao de continuar...", tm, TRUE);
//	
//	unsigned char dataRcv = 0;
//	unsigned char dataCmd[15] = {"\0\0\0\0\0\0\0\0\0\0\0\0\0\0"};
//	unsigned char dataCmdIndex = 0;
//	while(TRUE){
//		
//		while(TRUE){
//			Serial1_RecvChar(&dataRcv);
//			if(dataRcv == 'Z') break;
//			//(void)WDog1_Clear(NULL);
//		}
//		dataCmdIndex = 0;
//		while(TRUE){
//			wait(5200); //410
//			Serial1_RecvChar(&dataRcv);
//			if(dataRcv == 'X') break;
//			dataCmd[dataCmdIndex] = dataRcv;
//			if(dataCmdIndex < 14) dataCmdIndex++;
//		}
//		dataCmd[dataCmdIndex] = '\0';
//		
//		char cmdZX[3] = {"00"};
//		char valorZX[11];
//		int ZXc, ZXv;
//		cmdZX[0] = dataCmd[0];
//		cmdZX[1] = dataCmd[1];
//		ZXc = atoi(cmdZX);
//		int cont;
//		for(cont = 3; dataCmd[cont]; cont++){
//			valorZX[cont-3] = dataCmd[cont];
//		}
//		valorZX[cont-3] = '\0';
//		ZXv = atoi(valorZX);
//		
//		int iniciar = FALSE;
//		switch (ZXc) {
//			case 99:
//				iniciar = TRUE;
//				break;
//			case 1:
//				MAX_TRACAO = ZXv;
//				enviaVariavel("MAX_TRACAO ", MAX_TRACAO, tm);
//				break;
//			case 3:
//				WIDTH_TRACK = ZXv;
//				enviaVariavel("WIDTH_TRACK ", WIDTH_TRACK, tm);
//				break;
//			case 4:
//				WIDTH_TRACK_RANGE = ZXv;
//				enviaVariavel("WIDTH_TRACK_RANGE ", WIDTH_TRACK_RANGE, tm);
//				break;
//			case 5:
//				DELTA_AMOSTRA_MIN = ZXv;
//				enviaVariavel("DELTA_AMOSTRA_MIN ", DELTA_AMOSTRA_MIN, tm);
//				break;
//			case 12:
//				//01 deltaAmostra, 02 limiar, 03 bordaL, 04 bordaR, 05 diffBorda, 06 signalFeedback, 07 signalError, 08 signalControl
//				// 06 signalFeedback, 07 signalError, 08 signalControl_st, 09 signalControl_tr
//				v= ZXv;
//				if(v == 1) {
//					signalUART = &deltaAmostra;
//					ajusteUART = 0;
//					enviaString("Usando deltaAmostra", tm, TRUE);
//				}
//				else if(v == 2) {
//					signalUART = &limiar;
//					ajusteUART = 0;
//					enviaString("Usando Limiar", tm, TRUE);
//				}
//				else if(v == 3){ 
//					signalUART = &bordaL;
//					ajusteUART = 128;
//					enviaString("Usando bordaL", tm, TRUE);
//				}
//				else if(v == 4){
//					signalUART = &bordaR;
//					ajusteUART = 128;
//					enviaString("Usando bordaR", tm, TRUE);
//				}
//				else if(v == 5){
//					signalUART = &diffBorda;
//					ajusteUART = 0;
//					enviaString("Usando diffBorda", tm, TRUE);
//				}
//				else if(v == 6){
//					signalUART = &signalFeedback;
//					ajusteUART = 100;
//					enviaString("Usando SignalFeedback", tm, TRUE);
//				}
//				else if(v == 7){
//					signalUART = &signalError;
//					ajusteUART = 100;
//					enviaString("Usando SignalError", tm, TRUE);
//				}
//				else enviaString("Valor não existe!", tm, TRUE);
//				break;
//		}
//		
//		if(iniciar) break;
//		
//		//(void)WDog1_Clear(NULL);
//	}
//	
//	
//	////////////BLUE FIM ////////////
	
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
			
			bordaL = -1;
			bordaR = -1;
			for (auX_s = CENTCAML; auX_s >= 0; auX_s--) {
				if (!frameLine[auX_s]) {
					bordaL = auX_s;
					break;
				}
			}
			for (auY_s = CENTCAMR; auY_s < WIDTH_REAL; auY_s++) {
				if (!frameLine[auY_s]) {
					bordaR = auY_s;
					break;
				}
			}
			
			// FOR DEBUG - FIND THE CENTER OF DE CAR AND CAMERA     BEGIN
//			char leds = abs((CENTCAML - auX_s) - (auY_s - CENTCAMR));
//			if (leds == 0) acenderLeds(0b1111);
//			else if (leds == 1) acenderLeds(0b1110);
//			else if (leds == 2)	acenderLeds(0b1100);
//			else if (leds == 3) acenderLeds(0b1000);
//			else acenderLeds(0);
			// FOR DEBUG - FIND THE CENTER OF DE CAR AND CAMERA     END
			
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
				//if(signalErrorAbs > 25) signalError = 2*(signalError/signalErrorAbs)*MIN_ERRO;
			}

			#define KpMinTracao 1
			#define KpMaxTracao 2
			
			signalControlServo = signalError;
			signalControlTracao = signalError;
			//signalControlTracao = (KpMinTracao + (KpMaxTracao - KpMinTracao)*((float) (signalErrorAbs-MIN_ERRO)/MIN_ERRO)) * signalError;
	
			servo = ESQUERDA_SERVO	+ (DIREITO_SERVO - ESQUERDA_SERVO)*((float)(signalControlServo - MIN_ERRO)/RANGE_ERRO);
			setServo(servo);
			
		    motor2 = MAX_TRACAO + (MIN_TRACAO-MAX_TRACAO)*((float) (signalControlTracao)/(MAX_ERRO));
		    motor1 = MIN_TRACAO + (MAX_TRACAO-MIN_TRACAO)*((float) (signalControlTracao-MIN_ERRO)/(-MIN_ERRO));
			
			setTracao(motor1, motor2);
			
			//Serial1_SendChar(((unsigned char) *signalUART)+ajusteUART);
		}
		
		if(indiceY > LINEBOOST && indiceY < LINEBOOST+2){
			maiorAmostraBoost = 0;
			menorAmostraBoost = 255;
			for (auXBoost = MINBOOST; auXBoost < MAXBOOST; auXBoost++) {
				if (maiorAmostraBoost < frameBuffer1[LINEBOOST][auXBoost]) maiorAmostraBoost = frameBuffer1[LINEBOOST][auXBoost];
				if (menorAmostraBoost > frameBuffer1[LINEBOOST][auXBoost]) menorAmostraBoost = frameBuffer1[LINEBOOST][auXBoost];
			}
			deltaAmostraBoost = maiorAmostraBoost - menorAmostraBoost;
			
			limiarBoost = ((float) deltaAmostraBoost / 2) + menorAmostraBoost + 3;
			for (auXBoost = MINBOOST; auXBoost < MAXBOOST; auXBoost++) {
				frameLineBoost[auXBoost - MINBOOST] = frameBuffer1[LINEBOOST][auXBoost] > limiarBoost;
			}
			
			bordaLBoost = -1;
			bordaRBoost = -1;
			for (auX_s = CENTBOOSTL; auX_s >= 0; auX_s--) {
				if (!frameLineBoost[auX_s]) {
					bordaLBoost = auX_s;
					break;
				}
			}
			for (auY_s = CENTBOOSTR; auY_s < WIDTH_REALBOOST; auY_s++) {
				if (!frameLineBoost[auY_s]) {
					bordaRBoost = auY_s;
					break;
				}
			}

			diffBordaBoost = 0;
			if(deltaAmostraBoost > DELTA_AMOSTRA_MIN){
				if((bordaLBoost != -1) && (bordaRBoost != -1)){
//					//Tenta achar duas linhas
					diffBordaBoost = bordaRBoost - bordaLBoost;
					if(diffBordaBoost > 19) typeTrack = RETA;
					else typeTrack = CURVA;
				}
				else typeTrack = CURVA;
			}
			else typeTrack = CURVA;
			
			if(typeTrack){
				//RETA
				contRetas++;
				if(contRetas > 20){
					acenderLeds(0b1111);
					MAX_TRACAO = 1;
					isBoost = TRUE;
					contaCurvas = 0;
					contaFreio = 0;
					MIN_TRACAO = 400;
					contRetas = 21;
				}
			}
			else {
				//CURVA
				MIN_TRACAO = 900;
				if(isBoost){
					contaCurvas++;
					if(contaCurvas > 40){
						MAX_TRACAO = 700;
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
						if(contaFreio > 128) isFreio = FALSE;
					}
					else {
						MAX_TRACAO = 1;
					}
				}
			}
			
		}
		
		//Novo Quadro Capturado!
		if (frameFlag) {
			frameFlag = FALSE;
			indiceY = 0;
			//(void)WDog1_Clear(NULL);
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
