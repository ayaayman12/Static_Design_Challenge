/*
 * Steering.c
 *
 * Created: 2/18/2020 6:53:51 PM
 *  Author: A_ayman
 */ 

#include "Steering.h"

ERROR_STATUS Steering_Init()
{
	uint8_t u8_Ret= E_OK;
   Motor_Init(MOTOR_1);
   Motor_Init(MOTOR_2);
	return u8_Ret;
}
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	uint8_t u8_Ret=E_OK;
	switch(Steering_CarCmd)
   {
	   case CAR_STOP	:
		{
			Motor_Direction( MOTOR_1,MOTOR_STOP);
			Motor_Direction( MOTOR_2,MOTOR_STOP);
			break;
		}
		case CAR_FORWARD	:
		{
			Motor_Start( MOTOR_1,speed);
			Motor_Start( MOTOR_2,speed);
			Motor_Direction( MOTOR_1,MOTOR_FORWARD);
			Motor_Direction( MOTOR_2,MOTOR_FORWARD);
			break;
		}
		case CAR_BACKWARD	:
		{
			Motor_Start( MOTOR_1,speed);
			Motor_Start( MOTOR_2,speed);
			Motor_Direction( MOTOR_1,MOTOR_BACKWARD);
			Motor_Direction( MOTOR_2,MOTOR_BACKWARD);
			break;
		}
		case CAR_RIGHT:
		{
			Motor_Start( MOTOR_1,speed);
			Motor_Start( MOTOR_2,speed);
			Motor_Direction( MOTOR_1,MOTOR_FORWARD);
			Motor_Direction( MOTOR_2,MOTOR_BACKWARD);
			break;
		}
		case CAR_LEFT:
		{
			Motor_Start( MOTOR_1,speed);
			Motor_Start( MOTOR_2,speed);
			Motor_Direction( MOTOR_1,MOTOR_BACKWARD);
			Motor_Direction( MOTOR_2,MOTOR_FORWARD);
			break;
		}
		default:
		{
			u8_Ret=E_NOK;
			break;
		}
		
				
	}
	
	return u8_Ret;
}