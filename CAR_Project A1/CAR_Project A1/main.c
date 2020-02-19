/*
 * CAR_Project A1.c
 *
 * Created: 2/19/2020 7:33:13 AM
 * Author : A_ayman
 */ 

#include "car_sm.h"
#include "motor.h"
#include "interrupts.h"
#include "Steering.h"
#include <util/delay.h>


int main(void)
{
	 Car_SM_Init();
    /* Replace with your application code */
    while (1) 
    {
		  Car_SM_Update();
		  _delay_ms(100);
    }
}

