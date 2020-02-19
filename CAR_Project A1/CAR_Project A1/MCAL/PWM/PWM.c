/*
 * PWM.c
 *
 * Created: 2/17/2020 7:32:57 PM
 *  Author: A_ayman
 */ 
#include "PWM.h"

#define T1_PHASECORRECT_MODE_ICR1_TOP    0x0210
#define T1_OC1A_CLEAR                    0x8000
#define T1_OC1B_CLEAR                    0x2000
#define T1_PRESCALER_256                 0x0004
#define T1_POLLING                       0
#define T1_NO_CLOCK                      0x0000
uint16_t gu16_prscaller= T1_PRESCALER_256 ;
uint8_t gu8PWM_Start_Flag=0;

ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg)
{
	 uint8_t u8_Ret=E_OK;
	 if (Pwm_Cfg != NULL)
	 {
	    switch(Pwm_Cfg->Channel)
	    {
		    case PWM_CH0 : break;
		    case PWM_CH1A:
		    {
			    TCCR1|=(T1_PHASECORRECT_MODE_ICR1_TOP|T1_OC1A_CLEAR);
			    TIMSK|=T1_POLLING;
			    break;
		    }
		    case PWM_CH1B:
		    {
			    TCCR1|=(T1_PHASECORRECT_MODE_ICR1_TOP|T1_OC1B_CLEAR);
			    TIMSK|=T1_POLLING;
			    break;
		    }
		    case PWM_CH2 : break;
		    default: u8_Ret =E_NOK; break;
	    }
	 }
	 else
	 {
	    u8_Ret =E_NOK;
	 }
	 
	 return u8_Ret;
}
ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{
	uint8_t u8_Ret=E_OK;
	uint32_t au32_OCR1A_Counts=0;
	uint32_t au32_OCR1B_Counts=0;
	switch(Channel)
	{
		case PWM_CH0 : break;
		case PWM_CH1A:
		{
			switch (Frequncy)
			{
				case (T0_FERQ_50) :
				{
					ICR1 =625;
					au32_OCR1A_Counts=6.25* Duty;
					OCR1A=au32_OCR1A_Counts;
					break;
				}
				case (T0_FERQ_100):
				{
					ICR1 =312.5;
					au32_OCR1A_Counts=3.125* Duty;
					OCR1A=au32_OCR1A_Counts;
					break;
				}
				default:	u8_Ret=E_NOK; break;
			}
			break;
		}
		case PWM_CH1B:
		{
			switch (Frequncy)
			{
				case (T0_FERQ_50) :
				{
					ICR1 =625;
					au32_OCR1B_Counts=6.25* Duty;
					OCR1B=au32_OCR1B_Counts;
					break;
				}
				case (T0_FERQ_100):
				{
				   ICR1 =312.5;
				   au32_OCR1B_Counts=3.125* Duty;
				   OCR1B=au32_OCR1B_Counts; 
				   break;
		    	}
			}

			break;
		}
		case PWM_CH2 : break;
		default: u8_Ret=E_NOK; break;
	}
	/* Set Prescaler to start timer */
	TCCR1|= T1_PRESCALER_256;
	if (u8_Ret==E_OK)
	{
		 gu8PWM_Start_Flag=1;
	}
	return u8_Ret;
}

ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequncy)
{
	uint8_t u8_Ret=E_OK;
	uint32_t au32_OCR1A_Counts=0;
	uint32_t au32_OCR1B_Counts=0;
	if (gu8PWM_Start_Flag==1)
	{
	   switch(Channel)
	   {
		   case PWM_CH0 : break;
		   case PWM_CH1A:
		   {
			   switch (Frequncy)
			   {
				   case (T0_FERQ_50) :
				   {
					   ICR1 =625;
					   au32_OCR1A_Counts=6.25* Duty;
					   OCR1A=au32_OCR1A_Counts;
					   break;
				   }
				   case (T0_FERQ_100):
				   {
					   ICR1 =312.5;
					   au32_OCR1A_Counts=3.125* Duty;
					   OCR1A=au32_OCR1A_Counts;
					   break;
				   }
					default:	u8_Ret=E_NOK; break;
			   }
			   break;
		   }
		   case PWM_CH1B:
		   {
			   switch (Frequncy)
			   {
				   case (T0_FERQ_50) :
				   {
					   ICR1 =625;
					   au32_OCR1B_Counts=6.25* Duty;
					   OCR1B=au32_OCR1B_Counts;
					   break;
				   }
				   case (T0_FERQ_100):
				   {
					   ICR1 =312.5;
					   au32_OCR1B_Counts=3.125* Duty;
					   OCR1B=au32_OCR1B_Counts;
					   break;
				   }
					default:	u8_Ret=E_NOK; break;
			   }
			   break;
		   }
		   case PWM_CH2 : break;
			default:	u8_Ret=E_NOK; break;
	   }
	   /* Set Prescaler to start timer */
	   TCCR1|= T1_PRESCALER_256;
    }
	 else
	 {
		  u8_Ret=E_NOK;
	 }
	 return u8_Ret;
}

ERROR_STATUS Pwm_Stop(uint8_t Channel)
{
	uint8_t u8_Ret=E_OK;
	switch(Channel)
	{
		case PWM_CH0 : break;
		case PWM_CH1A:
		{
			OCR1A=0;
			/*to stop timer*/
			TCCR1&=~(0x0007);
			TCCR1|=T0_NO_CLOCK;
			
			break;
		}
		case PWM_CH1B:
		{
		   OCR1B=0;
		   /*to stop timer*/
		   TCCR1&=~(0x0007);
		   TCCR1|=T0_NO_CLOCK;
			break;
		}
		case PWM_CH2 : break;
		default: u8_Ret=E_NOK; break;
	}
	return u8_Ret;
}