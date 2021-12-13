/* ###################################################################
**     Filename    : Events.c
**     Project     : SmartTrackerRCA1
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-26, 00:14, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "dados.h"

extern uint8_t frameBuffer1[HEIGHT][WIDTH];
extern char frameFlag;
extern char saltoEmY;
extern char indiceY;
/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  CamVSync_OnInterrupt (module Events)
**
**     Component   :  CamVSync [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void CamVSync_OnInterrupt(void)
{
  /* Write your code here ... */
	CamHSync_Enable();
	CamVSync_Disable();
}

/*
** ===================================================================
**     Event       :  CamHSync_OnInterrupt (module Events)
**
**     Component   :  CamHSync [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void CamHSync_OnInterrupt(void)
{
  /* Write your code here ... */
	if(saltoEmY){
		if(saltoEmY == 2){
			CamDMA_SetDestinationAddress(CamDMA_DeviceData, &frameBuffer1[indiceY][0]);
			CamDMA_SetRequestCount(CamDMA_DeviceData, WIDTH);
			indiceY++;
			if(indiceY > HEIGHT-1){
				CamHSync_Disable();
				frameFlag = TRUE;
			}
		}
		saltoEmY--;
	}
	else {
		saltoEmY = 3;
		CamDMA_EnableRequest(CamDMA_DeviceData);
	}
}

/*
** ===================================================================
**     Event       :  Relogio1_OnInterrupt (module Events)
**
**     Component   :  Relogio1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Relogio1_OnInterrupt(void)
{
  /* Write your code here ... */
//  //DEBUG DE SERVO MOTOR!!!
//	static int cont;
//	cont++;
//	static int opcao;
//	if(cont >= 4){
//		cont = 0;
//		if(opcao == 0)      setServo(CENTRO_SERVO);
//		else if(opcao == 1) setServo(ESQUERDA_SERVO);
//		else if(opcao == 2) setServo(CENTRO_SERVO);
//		else if(opcao == 3) setServo(DIREITO_SERVO);
//		opcao++;
//		if(opcao > 3) opcao = 0;
//	}
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
