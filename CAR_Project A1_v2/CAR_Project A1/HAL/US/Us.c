/*
 * Us.c
 *
 * Created: 2/18/2020 1:24:52 PM
 *  Author: A_ayman
 */ 
#include "Us.h"  
#include <util/delay.h>

#define TRIGGER_BIT BIT0
#define TRIGGER_PORT GPIOA
#define TIMER_RESOLUTION_US (256/16)
/*volatile uint32_t gu32_Time_Tacken*/
volatile uint16_t gu16_Distance=ZERO;

ERROR_STATUS Us_Init(void)
{
	uint8_t u8_Ret=E_OK;
	/* Configuration of trigger pin*/
	strDIOCfg_t Dio_Trigger={TRIGGER_PORT,TRIGGER_BIT,OUTPUT};
	u8_Ret|=DIO_Init(&Dio_Trigger);
	/* Configuration of ICU*/
	Icu_cfg_s Icu_Cfg;
	Icu_Cfg.ICU_Ch_Timer=TIMER_0;
	Icu_Cfg.ICU_Ch_No=ICU_CH2;
	u8_Ret|=Icu_Init(&Icu_Cfg);
	u8_Ret|=Icu_ReadTime(Icu_Cfg.ICU_Ch_No, ICU_FALE_TO_RISE,&gu32_Time_Ticks);
	return u8_Ret;
}
ERROR_STATUS Us_Trigger(void)
{
	 uint8_t u8_Ret=E_OK;
	 u8_Ret|=DIO_Write(TRIGGER_PORT,TRIGGER_BIT,HIGH);
	 _delay_us(15);
  	u8_Ret|= DIO_Write(TRIGGER_PORT,TRIGGER_BIT,LOW);
   return u8_Ret;

}
ERROR_STATUS Us_GetDistance()
{
	uint8_t u8_Ret=E_OK;
	uint32_t u32_OF_Ticks=ZERO;
	volatile uint32_t u32_Time_Us=ZERO;
	uint32_t u32_Total_Ticks=ZERO;
	u32_OF_Ticks=gu8_Over_FlowCounts*T0_COUNTS;
	u32_Total_Ticks=(u32_OF_Ticks+gu32_Time_Ticks);
	u32_Time_Us=u32_Total_Ticks*TIMER_RESOLUTION_US;       //16 is output of (256/16000000) to get time in us; 
	gu16_Distance =((u32_Time_Us)/58.0);
	_delay_ms(20);
	gu8_Over_FlowCounts=ZERO;
	return u8_Ret;

}