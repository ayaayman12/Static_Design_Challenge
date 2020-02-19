/*
 * motor.c
 *
 * Created: 2/16/2020 10:05:28 PM
 *  Author: A_ayman
 */ 

#include "motor.h"
volatile uint8_t gu8_DutyCycle=0;

 ERROR_STATUS Motor_Init(uint8_t Motor_Number)
 {
	 strDIOCfg_t Dio_motor;
	 uint8_t u8_Ret=E_OK;
    if(Motor_Number==1)
	 {
		  /*set direction for motor1*/
		  Dio_motor.GPIO=MOTOR_OUT_1A_GPIO;
		  Dio_motor.pins=MOTOR_OUT_1A_BIT|MOTOR_OUT_1B_BIT|MOTOR_EN_1_BIT;
		  Dio_motor.dir=OUTPUT;
	  	  u8_Ret|=DIO_Init(&Dio_motor);
	 }
	 else if(Motor_Number==2)
	 {
		    Dio_motor.GPIO=MOTOR_OUT_2A_GPIO;
		    Dio_motor.pins=MOTOR_OUT_2A_BIT|MOTOR_OUT_2B_BIT|MOTOR_EN_2_BIT;
		    Dio_motor.dir=OUTPUT;
		    u8_Ret|=DIO_Init(&Dio_motor);

	 }
	 else
	 {
		  /*do nothing just indicate that function not working well*/
		  u8_Ret= E_NOK;
		  
	 }
	  Pwm_Cfg_s Pwm_Cfg;
	  Pwm_Cfg_s Pwm_Cfg1;
	  Pwm_Cfg.Channel =PWM_CH1A;
	  Pwm_Cfg.Prescaler=0;
	  
    Pwm_Cfg1.Channel =PWM_CH1B;
    Pwm_Cfg1.Prescaler=0;
    u8_Ret|=Pwm_Init(&Pwm_Cfg); //for motor one 
	 u8_Ret|=Pwm_Init(&Pwm_Cfg1);//for motor two
	 return u8_Ret;
	 
 }
 
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
	uint8_t u8_Ret=E_OK; 
	if (Motor_Number==MOTOR_1)
	{
		switch (Motor_Direction)
		{
			case (MOTOR_STOP):
			{
				u8_Ret|=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
				u8_Ret|=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
				break;
			}
			case (MOTOR_FORWARD):
			{
				u8_Ret|=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
				u8_Ret|=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
				break;
			}
			case (MOTOR_BACKWARD):
			{
				u8_Ret|=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
				u8_Ret|=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
				break;
			}
			default: u8_Ret=E_NOK; break;
			
		}
	}
	else if (MOTOR_2) //case motor 2
	{
		switch (Motor_Direction)
		{
			case (MOTOR_STOP):
			{
				u8_Ret|=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
				u8_Ret|=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
				break;
			}
			case (MOTOR_FORWARD):
			{
				u8_Ret|=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
				u8_Ret|=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
				break;
			}
			case (MOTOR_BACKWARD):
			{
				u8_Ret|=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
				u8_Ret|=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);
				break;
			}
			default: u8_Ret=E_NOK; break;
			
		}
	}
	else
	{
		 u8_Ret=E_NOK;
	}
	return u8_Ret;
}

ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{
   uint8_t u8_Ret=E_OK;
   gu8_DutyCycle=Mot_Speed;
	switch(Motor_Number)
	{
	   case (MOTOR_1):
		{
		   u8_Ret|=Pwm_Start(PWM_CH1A,gu8_DutyCycle,T0_FERQ_50);
			u8_Ret=E_OK;
			break;
		}
		case (MOTOR_2):
		{
		   u8_Ret|=Pwm_Start(PWM_CH1B,gu8_DutyCycle,T0_FERQ_50);
			u8_Ret=E_OK;
			break;
		}
		default:	u8_Ret=E_NOK; break;
	}
	return u8_Ret; 
}
ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
	uint8_t u8_Ret=E_OK;
	gu8_DutyCycle=Speed;
	switch(Motor_Number)
	{
		case (MOTOR_1):
		{
			u8_Ret|=Pwm_Update(PWM_CH1A,gu8_DutyCycle,T0_FERQ_50);
			break;
		}
		case (MOTOR_2):
		{
			u8_Ret|=Pwm_Update(PWM_CH1B,gu8_DutyCycle,T0_FERQ_50);
			break;
		}
		default: u8_Ret=E_NOK; break;
	}
	return u8_Ret;
	
}
ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	 uint8_t u8_Ret=E_OK; 
	 if (Motor_Number==MOTOR_1)
	 {
		  u8_Ret|=DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,LOW);
		  u8_Ret|=DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,LOW);
		  u8_Ret|=DIO_Write(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,LOW);
	 }
	 else if (Motor_Number==MOTOR_2)
	 {
		  u8_Ret|=DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,LOW);
		  u8_Ret|=DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,LOW);
		  u8_Ret|=DIO_Write(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,LOW);
	
	 }
	 else 
	 {
		  u8_Ret=E_NOK;
	 }
	 return u8_Ret;
	 
}