/*
 * Steering.c
 *
 * Created: 2/18/2020 6:53:51 PM
 *  Author: A_ayman
 */ 

#include "Steering.h"

/* this function is used to set motors directions */
ERROR_STATUS Steering_Init()
{
	uint8_t u8_Ret= E_OK;
   u8_Ret|=Motor_Init(MOTOR_1);
   u8_Ret|=Motor_Init(MOTOR_2);
	return u8_Ret;
}
/* this function is used to determine motors directions and speed based on the steering command you send */
/* you can either choose among moving the car forward, backward, right, left, or even stop it*/ 
ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	uint8_t u8_Ret=E_OK;
	switch(Steering_CarCmd)
   {
	   case CAR_STOP	:
		{
			u8_Ret|=Motor_Direction( MOTOR_1,MOTOR_STOP);
			u8_Ret|=Motor_Direction( MOTOR_2,MOTOR_STOP);
			break;
		}
		case CAR_FORWARD	:
		{
			u8_Ret|=Motor_Start( MOTOR_1,speed);
			u8_Ret|=Motor_Start( MOTOR_2,speed);
			u8_Ret|=Motor_Direction( MOTOR_1,MOTOR_FORWARD);
			u8_Ret|=Motor_Direction( MOTOR_2,MOTOR_FORWARD);
			break;
		}
		case CAR_BACKWARD	:
		{
			u8_Ret|=Motor_Start( MOTOR_1,speed);
			u8_Ret|=Motor_Start( MOTOR_2,speed);
			u8_Ret|=Motor_Direction( MOTOR_1,MOTOR_BACKWARD);
			u8_Ret|=Motor_Direction( MOTOR_2,MOTOR_BACKWARD);
			break;
		}
		case CAR_RIGHT:
		{
			u8_Ret|=Motor_Start( MOTOR_1,speed);
			u8_Ret|=Motor_Start( MOTOR_2,speed);
			u8_Ret|=Motor_Direction( MOTOR_1,MOTOR_FORWARD);
			u8_Ret|=Motor_Direction( MOTOR_2,MOTOR_BACKWARD);
			break;
		}
		case CAR_LEFT:
		{
			u8_Ret|=Motor_Start( MOTOR_1,speed);
			u8_Ret|=Motor_Start( MOTOR_2,speed);
			u8_Ret|=Motor_Direction( MOTOR_1,MOTOR_BACKWARD);
			u8_Ret|=Motor_Direction( MOTOR_2,MOTOR_FORWARD);
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