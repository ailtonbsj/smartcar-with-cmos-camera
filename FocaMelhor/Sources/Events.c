/* ###################################################################
**     Filename    : Events.c
**     Project     : CamNtscUsingDma
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-04, 15:20, # CodeGen: 0
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
extern char FrameFlag;
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
			if(indiceY > HEIGHT-1)
			{
				CamHSync_Disable();
				FrameFlag = TRUE;
			}
		}
		saltoEmY--;
	}
	else {
		saltoEmY = 3;
		CamDMA_EnableRequest(CamDMA_DeviceData);		
	}
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
