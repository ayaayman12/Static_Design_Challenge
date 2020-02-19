/*
 * ICU.c
 *
 * Created: 2/17/2020 11:41:17 AM
 *  Author: A_ayman
 */ 
#include "DIO.h"
#include "ICU.h"



/*SwICU_Edge_ mask*/
#define SWICU_EDGEFALLING  0
#define SWICU_EDGERISING  0x40

/* variables*/

gstr_TimerCfg_t  gst_Timer_Cfg;

//volatile uint32_t gu32_Time_Ticks=ZERO;
uint32_t gu32_Time_Ticks=ZERO;
volatile uint8_t gu8_Mission_Complete=ZERO;

ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{	 
	uint8_t u8_Ret=E_OK;
	if(Icu_Cfg !=NULL)
	{
	   sei();//enable global interrupt
	   /* determine which timer channel to use */
	   switch(Icu_Cfg->ICU_Ch_Timer)
	   {
		   case (ICU_TIMER_CH0):
		   {
			   gst_Timer_Cfg.Timer_Ch=TIMER_0;
			   gst_Timer_Cfg.Timer_Mode=TIMER_MODE;
			   gst_Timer_Cfg.Timer_Prescaler=T0_PRESCALER_256;
			   gst_Timer_Cfg.Timer_INT_Mode=T0_INTERRUPT_NORMAL;
			   u8_Ret|=Timer_Init(&gst_Timer_Cfg);
			   break;
		   }
		   
		   case (ICU_TIMER_CH1):
		   {
			   gst_Timer_Cfg.Timer_Ch=TIMER_1;
			   gst_Timer_Cfg.Timer_Mode=TIMER_MODE;
			   gst_Timer_Cfg.Timer_Prescaler=T1_PRESCALER_256;
			   gst_Timer_Cfg.Timer_INT_Mode=T1_INTERRUPT_NORMAL;
			   u8_Ret|=Timer_Init(&gst_Timer_Cfg);
			   break;
		   }
		   case (ICU_TIMER_CH2):
		   {
			   gst_Timer_Cfg.Timer_Ch=TIMER_2;
			   gst_Timer_Cfg.Timer_Mode=TIMER_MODE;
			   gst_Timer_Cfg.Timer_Prescaler=T0_PRESCALER_8;
			   gst_Timer_Cfg.Timer_INT_Mode=T2_INTERRUPT_NORMAL;
			   u8_Ret|=Timer_Init(&gst_Timer_Cfg);
			   break;
		   }
		   default: u8_Ret= E_OK; break;
		   
		   
	   }
	   /*Set External interrupt pin as input*/
	   strDIOCfg_t DIO;
	   DIO.GPIO=INT_2_GPIO;
	   DIO.pins=INT_2_BIT;
	   DIO.dir=INPUT;
	   u8_Ret|=DIO_Init(&DIO);
	}
	else
	{
		u8_Ret=E_NOK;
	}
	 
	 return u8_Ret;
	
	}

ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
{
	uint8_t u8_Ret=E_OK;
	uint16_t u16_Timer_Counts=ZERO;
   /* determine which External interrupt to use */
	switch(Icu_Channel)
	{
		case (ICU_CH0):
		{
			/* configuration of using INT0*/
		   break;
		}
		case (ICU_CH1):
		{
			/* configuration of using INT1*/
			break;
		}
		case (ICU_CH2):
		{
			/*SwICU_INT_Disable*/
			GICR&=~(INT2);
			
			MCUCSR&=~ISC2;
			switch(Icu_EdgeToEdge)
			{
			   case (ICU_RISE_TO_RISE):
				{
					//MCUCSR|=SWICU_EDGEFALLING;
				   break;
				}
				case (ICU_RISE_TO_FALL):
				{
					/*ISC2 is written to ZERO, SO a Falling edge on INT2 activates the interrupt*/
					MCUCSR|=SWICU_EDGEFALLING;
					break;
				}
				case (ICU_FALE_TO_RISE):
				{
					/*ISC2 is written to one, SO a rising edge on INT2 activates the interrupt*/
					MCUCSR|=SWICU_EDGERISING;
					break;
				}
				default: u8_Ret=E_NOK; break;
			}
			GIFR&=~INTF2;
			
		   /*SwICU_INT_Enable*/
			GICR|=INT2;
	   }
		default: u8_Ret=E_NOK; break;
		  
   }
   /*this function will return the ticks of the chosen channel timer*/
   u8_Ret|=Timer_GetValue(TIMER_0,&u16_Timer_Counts);
	*Icu_Time=u16_Timer_Counts;
	
	return u8_Ret;
}


ISR(INT2_vect)
{
	
	switch (gu8_Mission_Complete)
	{
		case 0:
		{
			
		   Timer_Start(ICU_TIMER_CH0,T0_COUNTS);
		   Icu_ReadTime(ICU_CH2,ICU_RISE_TO_FALL,&gu32_Time_Ticks);
		   gu8_Mission_Complete=1;
		   break;
		}		
		case 1:
		{
			Icu_ReadTime(ICU_CH2,ICU_FALE_TO_RISE,&gu32_Time_Ticks);
			Timer_Stop(ICU_TIMER_CH0);
			/*gu8_Mission_Complete=2;*/
			gu8_Mission_Complete=0;
			break;
		}
	}
}
