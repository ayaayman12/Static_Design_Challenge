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
/*volatile uint32_t gu32_Time_Tacken*/
volatile uint16_t gu16_Distance=ZERO;

ERROR_STATUS Us_Init(void)
{
	uint8_t u8_Ret=E_OK;
	/* Configuration of trigger pin*/
	strDIOCfg_t Dio_Trigger={TRIGGER_PORT,TRIGGER_BIT,OUTPUT};
	DIO_init(&Dio_Trigger);
	/* Configuration of ICU*/
	Icu_cfg_s Icu_Cfg;
	Icu_Cfg.ICU_Ch_Timer=TIMER_0;
	Icu_Cfg.ICU_Ch_No=ICU_CH2;
	Icu_Init(&Icu_Cfg);
	Icu_ReadTime(Icu_Cfg.ICU_Ch_No, ICU_FALE_TO_RISE,&gu32_Time_Ticks);
	return u8_Ret;
}
ERROR_STATUS Us_Trigger(void)
{
	 uint8_t u8_Ret=E_OK;
	 DIO_Write(TRIGGER_PORT,TRIGGER_BIT,HIGH);
	 _delay_us(15);
	 DIO_Write(TRIGGER_PORT,TRIGGER_BIT,LOW);
	 return u8_Ret;

}
ERROR_STATUS Us_GetDistance()
{
	uint8_t u8_Ret=E_OK;
	uint32_t u32_OF_Ticks=0;
	volatile uint32_t u32_Time_Us=0;
	uint32_t u32_Total_Ticks=0;
	u32_OF_Ticks=gu8_Over_FlowCounts*T0_COUNTS;
	u32_Total_Ticks=(u32_OF_Ticks+gu32_Time_Ticks);
	u32_Time_Us=u32_Total_Ticks*16;       //16 is output of (256/16000000); 
	gu16_Distance =((u32_Time_Us)/58.0);
	_delay_ms(20);
	gu8_Over_FlowCounts=0;
	return u8_Ret;

}