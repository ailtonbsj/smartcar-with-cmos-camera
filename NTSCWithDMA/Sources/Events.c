/* ###################################################################
**     Filename    : Events.c
**     Project     : NTSCWithDMA
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-01, 16:20, # CodeGen: 0
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
extern uint8_t frameBuffer[60][90];
extern char FrameFlag;
char saltoEmY = 2;
char indiceY = 0;

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
**     Event       :  CameraHSync_OnInterrupt (module Events)
**
**     Component   :  CameraHSync [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  CamDMA_OnComplete (module Events)
**
**     Component   :  CamDMA [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is enabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/

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
		if(saltoEmY == 3){
			indiceY++;
			CamDMA_SetDestinationAddress(CamDMA_DeviceData, &frameBuffer[indiceY][0]);
			CamDMA_SetRequestCount(CamDMA_DeviceData, 90);
			if(indiceY > 58)
			{
				CamHSync_Disable();
				FrameFlag = TRUE;
			}
		}
		saltoEmY--;
	}
	else {
		saltoEmY = 4;
		CamDMA_EnableRequest(CamDMA_DeviceData);		
	}
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
