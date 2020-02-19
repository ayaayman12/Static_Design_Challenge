/*
 * DIO.c
 *
 * Created: 2/15/2020 7:18:29 PM
 *  Author: A_ayman
 */ 
#include "DIO.h"

/* This function can set the direction of a full port, a nibble  or even one pin*/

ERROR_STATUS DIO_Init (strDIOCfg_t *gpstrDIO_info)
{
	uint8_t u8_Ret=E_OK;
	uint8_t au8_temp_reg;
	uint8_t au8_Masked_Pins;
	if (gpstrDIO_info != NULL)
	{
	   switch (gpstrDIO_info->GPIO)
	   {
		   case GPIOA:
		   {
			   au8_temp_reg = PORTA_DIR & ~(gpstrDIO_info->pins);
			   au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
			   PORTA_DIR= au8_temp_reg |au8_Masked_Pins ;
			   break;
		   }
		   case GPIOB:
		   {
			   au8_temp_reg = PORTB_DIR & ~(gpstrDIO_info->pins);
			   au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
			   PORTB_DIR= au8_temp_reg |au8_Masked_Pins ;
			   break;
		   }
		   case GPIOC:
		   {
			   au8_temp_reg = PORTC_DIR & ~(gpstrDIO_info->pins);
			   au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
			   PORTC_DIR= au8_temp_reg |au8_Masked_Pins ;
			   break;
		   }
		   case GPIOD:
		   {
			   au8_temp_reg = PORTD_DIR & ~(gpstrDIO_info->pins);
			   au8_Masked_Pins =(gpstrDIO_info->pins & gpstrDIO_info->dir);
			   PORTD_DIR= au8_temp_reg |au8_Masked_Pins ;
			   break;
		   }
		   default:	u8_Ret= E_NOK; break;
	   }
	}
	else
	{
	   u8_Ret= E_NOK;
		 
	}
	
	return u8_Ret;
}

/*This function can set the value of a full port, a nibble or even one pin*/
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
	uint8_t u8_Ret=E_OK;
	uint8_t au8_temp_reg;
	uint8_t au8_Masked_Pins;
	switch (GPIO)
	{
		case GPIOA:
		{
			au8_temp_reg = PORTA_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTA_DATA= au8_temp_reg |au8_Masked_Pins ;
			break;
		}
		case GPIOB:
		{
			au8_temp_reg = PORTB_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTB_DATA= au8_temp_reg |au8_Masked_Pins ;
			break;
		}
		case GPIOC:
		{
			au8_temp_reg = PORTC_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTC_DATA= au8_temp_reg |au8_Masked_Pins ;
			break;
		}
		case GPIOD:
		{
			au8_temp_reg = PORTD_DATA & ~(pins);
			au8_Masked_Pins =(pins & value);
			PORTD_DATA= au8_temp_reg |au8_Masked_Pins ;
			break;
		}
		default: u8_Ret= E_NOK;	break; 
	}
	return u8_Ret; 
}

/*This function gets the value of a full port, a nibble or even one pin*/
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data)
{
	uint8_t u8_Ret =E_OK;
	switch (GPIO)
	{
		case (GPIOA): *data= PORTA_PIN & (pins); break;
		case (GPIOB): *data= PORTB_PIN & (pins); break;
		case (GPIOC): *data= PORTC_PIN & (pins); break;
		case (GPIOD): *data= PORTD_PIN & (pins); break;
		default:	u8_Ret=E_NOK; break;
	}
	return u8_Ret;
}

/* This function toggles the value of a full port, a nibble or even one pin */
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
	uint8_t u8_Ret =E_OK;
	switch (GPIO)
	{
		case GPIOA: PORTA_DATA^=pins; break;
		case GPIOB: PORTB_DATA^=pins; break;
		case GPIOC: PORTC_DATA^=pins; break;
		case GPIOD: PORTD_DATA^=pins; break;
		default:	u8_Ret= E_NOK; break;
	}
   return u8_Ret;
}