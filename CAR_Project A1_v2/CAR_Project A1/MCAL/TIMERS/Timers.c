/*
 * Timers.c
 *
 * Created: 2/12/2020 10:23:21 PM
 *  Author: A_ayman
 */ 

/* Inclusions*/

#include "Timers.h"


/*LOCAL MACROS*/


/*LOCAL Data types */


/*LOCAL FUNCTIONS PROTOTYPES */

/* GLOBAL STATIC VARIABLES */
static uint8_t gu8_Prescal_T0=ZERO;
static uint16_t gu8_Prescal_T1=ZERO;
static uint8_t gu8_Prescal_T2=ZERO;

/* GLOBAL EXTERN VARIABLES */
volatile uint8_t gu8_Over_FlowCounts=ZERO;

/*- APIs IMPLEMENTATION --*/






ERROR_STATUS Timer_Init(gstr_TimerCfg_t* gpstr_Timer_Cfg)
{  
	 uint8_t u8_Ret=E_OK;
	 if (gpstr_Timer_Cfg != NULL)
	 {
		  switch(gpstr_Timer_Cfg -> Timer_Ch)
		  {  
			  case TIMER_0 :
			  {   
					if(gpstr_Timer_Cfg->Timer_Mode==TIMER_MODE)
					{
						TCCR0|=gpstr_Timer_Cfg->Timer_Mode;
						TCCR0|=T0_NORMAL_MODE;       //fixed till now 
						TCCR0|=T0_OC0_DIS;           //fixed till now
						gu8_Prescal_T0=gpstr_Timer_Cfg->Timer_Prescaler;
						TIMSK|=gpstr_Timer_Cfg->Timer_INT_Mode;
					}
					else
					{
						 /* this to handle the functionality of using timer as counter*/
					}
					break;
			  
			  }
			  case TIMER_1 :
			  {  
					if(gpstr_Timer_Cfg->Timer_Mode==TIMER_MODE)
					{ 
						TCCR1|=gpstr_Timer_Cfg->Timer_Mode;
						gu8_Prescal_T1=gpstr_Timer_Cfg->Timer_Prescaler;
						TIMSK|=gpstr_Timer_Cfg->Timer_INT_Mode;
					}
					else
					{
						 /* this to handle the functionality of using timer1 as counter*/
					}
					break;
			  }
			  case TIMER_2 :
			  {
					if(gpstr_Timer_Cfg->Timer_Mode==TIMER_MODE)
					{
						TCCR2|=gpstr_Timer_Cfg->Timer_Mode;
						gu8_Prescal_T2=gpstr_Timer_Cfg->Timer_Prescaler;
						TIMSK|= gpstr_Timer_Cfg->Timer_INT_Mode;
						ASSR|=0;
					}
					else
					{
					  /* this to handle the functionality of using timer2 as counter*/
					}
					
					break;
			  }	
			  default: u8_Ret=E_NOK; break;
	      }
			
	 }
	 else
	 {
		  u8_Ret= E_NOK;
	 }
	 return u8_Ret;
 }

ERROR_STATUS Timer_SetValue(uint8_t Timer_Ch,uint16_t Count_No)
{
   uint8_t u8_Ret=E_OK;
	switch(Timer_Ch)
	{
		case TIMER_0 :
		{
			TCNT0=Count_No;
			break;
		}
		case TIMER_1 :
		{
			TCNT1=Count_No;
			break;
		}
		case TIMER_2 :
		{
			TCNT2=Count_No;
			break;
		}
		default : u8_Ret= E_NOK; break;
	}
	return u8_Ret;
}
ERROR_STATUS Timer_Start(uint8_t Timer_Ch, uint16_t Count_No)
{  
	uint8_t u8_Ret=E_OK;
   switch (Timer_Ch)
   {
	   case TIMER_0:
		{
			 TCCR0|=gu8_Prescal_T0;
			 TCNT0=T0_COUNTS-Count_No;
			 break;
		}
	   case TIMER_1:
		{
		   TCCR1|=gu8_Prescal_T1;
		   TCNT1=T1_COUNTS-Count_No;
			break;
		}
		case TIMER_2:
		{
			TCCR2|=gu8_Prescal_T2;
			TCNT2=T2_COUNTS-Count_No;
			break;
		}
		default: u8_Ret= E_NOK;	break;
   }
	return u8_Ret;
}
ERROR_STATUS Timer_Stop(uint8_t Timer_Ch)
{
	uint8_t u8_Ret=E_OK;
	switch (Timer_Ch)
	{
		case TIMER_0:
		 TCCR0&=~(T_PRESCALLER_REMOVE);
		// TCNT0=0;
		  break;
		case TIMER_1: TCCR1B&=~(T_PRESCALLER_REMOVE); break;
		case TIMER_2: TCCR2&=~(T_PRESCALLER_REMOVE);	break;
		default:	u8_Ret= E_NOK; break;
	}
	
	return u8_Ret;
}

ERROR_STATUS Timer_GetValue(uint8_t Timer_Ch,uint16_t* Timer_Value)
{
	uint8_t u8_Ret=E_OK;
	switch (Timer_Ch)
	{
		case TIMER_0: * Timer_Value=TCNT0; break;
		case TIMER_1: * Timer_Value=TCNT1; break;
		case TIMER_2: * Timer_Value=TCNT2;	break;
		default:	u8_Ret= E_NOK; break;
	}
	return u8_Ret;
}

ERROR_STATUS Timer_GetStatus(uint8_t Timer_Ch,uint16_t* Timer_Status)
{   
	uint8_t u8_Ret=E_OK;
	switch(Timer_Ch)
	{
		case TIMER_0:
		{
		   if(TIFR>>TOV0!=ZERO)
			{
				*Timer_Status=OVER_FLOW_OCCUR;
				TIFR|=(1<<TOV0); //reset timer over flow
			}
			else if(TIFR>>TOV0==ZERO)
			{
				*Timer_Status=OVER_FLOW_NOT_OCCUR;
			}
			else
			{
				u8_Ret=E_NOK;
			}
			break;
		}
		case TIMER_1:
		{
			if(TIFR>>TOV1!=ZERO)
			{
				*Timer_Status=OVER_FLOW_OCCUR;
				TIFR|=(1<<TOV1); //reset timer over flow
			}
			else if(TIFR>>TOV1==ZERO)
			{
				*Timer_Status=OVER_FLOW_NOT_OCCUR;
			}
			else
			{
				u8_Ret=E_NOK;
			}
			break;
		}
		case TIMER_2:
		{
			if(TIFR>>TOV2!=ZERO)
			{
				*Timer_Status=OVER_FLOW_OCCUR;
				TIFR|=(1<<TOV2); //reset timer over flow
			}
			else if(TIFR>>TOV2==ZERO)
			{
				*Timer_Status=OVER_FLOW_NOT_OCCUR;
			}
			else
			{
				u8_Ret=E_NOK;
			}
			break;
		}
		default:u8_Ret=E_NOK;break; 
	}
 return u8_Ret; 
}


ISR (TIMER0_OVF_vect)
{
	 gu8_Over_FlowCounts++;
}

/* used for only testing timer interrupts*/

// ISR ( TIMER2_OVF_vect	)
// {
// 	
// 	gu8_Over_FlowCounts++;
// 	if(gu8_Over_FlowCounts==4)
// 	{
// 		DIO_Toggle (GPIOB, UPPER_NIBBLE);
// 		gu8_Over_FlowCounts=0;
// 	}
// 	TCNT2=6;
// }
// ISR ( TIMER1_OVF_vect	)
// {
// 	
// 	gu8_Over_FlowCounts++;
// 	if(gu8_Over_FlowCounts==4)
// 	{
// 		DIO_Toggle (GPIOB, UPPER_NIBBLE);
// 		gu8_Over_FlowCounts=0;
// 	}
// 	TCNT1=65286;
// }