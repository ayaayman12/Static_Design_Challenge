/*
 * car_sm.c
 *
 * Created: 2/18/2020 7:38:38 PM
 *  Author: A_ayman
 */ 


#include "Steering.h"
#include "Us.h"
#include <util/delay.h>
uint8_t u8_State=CAR_BACKWARD;

ERROR_STATUS Car_SM_Init(void)
{
	uint8_t u8_Ret= E_OK;
   Us_Init();
	Steering_Init();
	Steering_SteerCar(CAR_FORWARD, 30);
	return u8_Ret;

}
ERROR_STATUS Car_SM_Update(void)
{
	uint8_t u8_Ret =E_OK;
   Us_Trigger();
	 _delay_ms(20);
	Us_GetDistance();
   
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
	 
		 
	switch(u8_State)
	{
		/*case CAR_STOP:
		{
		   Steering_SteerCar(CAR_STOP, 30);
			break;
		}*/
		case CAR_FORWARD:
		{ /*it see it back*/
			Steering_SteerCar(CAR_FORWARD, 30);
			break;
		}
		case CAR_BACKWARD:
		{
			Steering_SteerCar(CAR_BACKWARD, 30);
			break;
		}
		case CAR_RIGHT:
		{
			Steering_SteerCar(CAR_RIGHT, 30);
			
			break;
		}
		default:	u8_Ret=E_NOK;break;
		}	 
   return u8_Ret;
}