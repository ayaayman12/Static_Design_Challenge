/*
 * Layer  : MCAL 
 * Module : PWM  
 * File   : Timers.h
 * Created: 2/12/2020 10:18:04 PM
 * Author : A_ayman
 * Description: TIMERS header file     
 */ 



#ifndef TIMERS_H_
#define TIMERS_H_

/* inclusions */

#include "DIO.h"
#include "registers.h"
#include "std_types.h"
#include "interrupts.h"
#include "module_retval.h"

/* Constants */

#define F_CPU 16000000

/* Timer Channels */
#define TIMER_0  0
#define TIMER_1  1
#define TIMER_2  2

/* Timer Modes */
#define TIMER_MODE   0
#define COUNTER_MODE 1

/*
*** Timer0_Prescaller
*/
#define T0_NO_CLOCK         0x00
#define T0_PRESCALER_NO     0x01
#define T0_PRESCALER_8      0x02
#define T0_PRESCALER_64     0x03
#define T0_PRESCALER_256    0x04
#define T0_PRESCALER_1024   0x05

/* Timer0_Modes */
#define T0_NORMAL_MODE   0
#define T0_COMP_MODE     0x08

/* Timer0_OC0_Modes */
#define T0_OC0_DIS    0x00
#define T0_OC0_TOGGLE 0x10
#define T0_OC0_CLEAR  0x20
#define T0_OC0_SET    0x30

/* Timer0_INT_Mode */
#define T0_POLLING          0x00
#define T0_INTERRUPT_NORMAL 0x01
#define T0_INTERRUPT_CMP    0x02


/* Timer1_INT_Mode */
#define T1_POLLING  0
#define T1_INTERRUPT_NORMAL 0x04
#define T0_INTERRUPT_CMP_1B 0x08
#define T1_INTERRUPT_CMP_1A 0x10
#define T1_INTERRUPT_ICAPTURE  0x20


/* Timer1_Prescaller */
#define T1_NO_CLOCK			 0x0000
#define T1_PRESCALER_NO		 0x0001
#define T1_PRESCALER_8		 0x0002
#define T1_PRESCALER_64		 0x0003
#define T1_PRESCALER_256	 0x0004
#define T1_PRESCALER_1024	 0x0005


/* Timer2_INT_Mode */
#define T2_POLLING 0
#define T2_INTERRUPT_NORMAL 0x40
#define T2_INTERRUPT_CMP 0x80


/* Timer_counts */
#define T0_COUNTS 256
#define T1_COUNTS 65536
#define T2_COUNTS 256

/*Timer Prescaller Remove mask*/
#define T_PRESCALLER_REMOVE 0x07
#define T1_PRESCALLER_REMOVE 0x0007

/* timer0 Modes*/
#define T0_NORMAL_MODE 0
#define T0_COMP_MODE 0x08

/*Timer Over flow Status*/
#define OVER_FLOW_OCCUR 1
#define OVER_FLOW_NOT_OCCUR 0

/*primitive types*/

extern volatile uint8_t gu8_Over_FlowCounts;

/*structures*/
typedef struct 
{
   uint8_t Timer_Ch;
	uint8_t Timer_Mode;
	uint8_t Timer_Prescaler;
	uint8_t Timer_INT_Mode;
}gstr_TimerCfg_t;


/*extern gstr_TimerCfg_t gst_Timer_Cfg;*/


/* function declarations*/

/******************************************************************************
* Function        : ERROR_STATUS Timer_Init(gstr_TimerCfg_t* Timer_Cfg);                    
* Type            : public                                                                  
* Input parameters: TimerCfg Structure (Timer_Channel, Timer_Mode, Timer_Prescaler, Timer_INT_Mode)               
* Return type     : ERROR_STATUS                                                            
*                                                                               
* Description: initialize the Timer configuration                                 
*****************************************************************************/

extern ERROR_STATUS Timer_Init(gstr_TimerCfg_t* Timer_Cfg);


/******************************************************************************
* Function        : ERROR_STATUS  Timer_Start(uint8_t Timer_Ch, uint16_t Count_No);
* Type            : public
* Input parameters: Timer_Channel, Count_No "the ticks number you want to count"
* Return type     : ERROR_STATUS
*
* Description: Start the Timer 
*****************************************************************************/
extern ERROR_STATUS  Timer_Start(uint8_t Timer_Ch, uint16_t Count_No);

/******************************************************************************
* Function        : ERROR_STATUS  Timer_Stop(uint8_t Timer_Ch);
* Type            : public
* Input parameters: Timer_Channel
* Return type     : ERROR_STATUS
*
* Description: Stop the Timer
*****************************************************************************/
extern ERROR_STATUS  Timer_Stop(uint8_t Timer_Ch);

/*************************************************************************
* Function        : ERROR_STATUS  Timer_GetValue(uint8_t Timer_Ch,uint16_t* Timer_Value);
* Type            : public
* Input parameters: Timer_Channel, (*Timer_Value)
* Return type     : ERROR_STATUS
*
* Description: Get the TCNTx value
*****************************************************************************/
extern ERROR_STATUS  Timer_GetValue(uint8_t Timer_Ch,uint16_t* Timer_Value);

/*************************************************************************
* Function        : ERROR_STATUS  Timer_SetValue(uint8_t Timer_Ch,uint16_t Count_No);
* Type            : public
* Input parameters: Timer_Channel, Count_No "the ticks number you want to count"
* Return type     : ERROR_STATUS
*
* Description: Set the TCNTx with your initial value
*****************************************************************************/
extern ERROR_STATUS  Timer_SetValue(uint8_t Timer_Ch,uint16_t Count_No);

/*************************************************************************
* Function        : ERROR_STATUS Timer_GetStatus(uint8_t Timer_Ch,uint16_t* Timer_Status);
* Type            : public
* Input parameters: Timer_Channel, (*Timer_Status)
* Return type     : ERROR_STATUS
*
* Description: Determine whether an Overflow happens or Not
*****************************************************************************/

extern ERROR_STATUS  Timer_GetStatus(uint8_t Timer_Ch,uint16_t* Timer_Status);




#endif /* TIMERS_H_ */