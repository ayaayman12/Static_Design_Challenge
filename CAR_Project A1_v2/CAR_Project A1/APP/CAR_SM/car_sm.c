/*
 * car_sm.c
 *
 * Created: 2/18/2020 7:38:38 PM
 *  Author: A_ayman
 */ 


#include "Steering.h"
#include "Us.h"
#include <util/delay.h>

#define DUTY_30 30
uint8_t u8_State=CAR_FORWARD;

ERROR_STATUS Car_SM_Init(void)
{
	uint8_t u8_Ret= E_OK;
   Us_Init();
	Steering_Init();
	Steering_SteerCar(CAR_FORWARD, DUTY_30);
	return u8_Ret;

}
ERROR_STATUS Car_SM_Update(void)
{
	uint8_t u8_Ret =E_OK;
   u8_Ret|=Us_Trigger();
	 _delay_ms(20);
	u8_Ret|=Us_GetDistance();
   
	if((gu16_Distance>=24)&&(gu16_Distance<=32))
	{
		 u8_State=CAR_RIGHT;
	}
	else if(gu16_Distance<24)
	{
		 u8_State=CAR_BACKWARD;
	}
	else if (gu16_Distance>32)
	{
		 u8_State=CAR_FORWARD;
	}
	/* select the right decision based on the state right now */
	switch(u8_State)
	{
		case CAR_STOP:
		{
		  u8_Ret|=Steering_SteerCar(CAR_STOP, DUTY_30);
			break;
		}
		case CAR_FORWARD:
		{ 
			u8_Ret|=Steering_SteerCar(CAR_FORWARD, DUTY_30);
			break;
		}
		case CAR_BACKWARD:
		{
			u8_Ret|=Steering_SteerCar(CAR_BACKWARD, DUTY_30);
			break;
		}
		case CAR_RIGHT:
		{
			u8_Ret|=Steering_SteerCar(CAR_RIGHT, DUTY_30);
			
			break;
		}
		default:	u8_Ret=E_NOK;break;
		}	 
   return u8_Ret;
}