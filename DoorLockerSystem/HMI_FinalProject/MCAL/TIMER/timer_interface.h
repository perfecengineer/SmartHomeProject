#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H
#include "../../UTILS/STD_TYPES.h"
#include "timer_configuration.h"
/*
 * The pre_build configuration for timer driver:
 */
#define SELECTION_MODULE0          TIMER0_ENABLE// TIMER0_ENABLE  OR COUNTER0_ENABLE OR DISABLE_MODULE
#define SELECTION_MODULE1          TIMER1_DISABLE// TIMER1_ENABLE  OR ICU_ENABLE OR COUNTER1_ENABLE OR DISABLE_MODULE
#define SELECTION_MODULE2          TIMER2_DISABLE// TIMER2_ENABLE OR COUNTER2_ENABLE OR DISABLE_MODULE

/*************************For Timer 0*********************************/
#if SELECTION_MODULE0    		 == 		   	 TIMER0_ENABLE
/************* Select mode for timer 0 *****************/
#define TIMER0_SELECTION_MODE   				 NORMAL_MODE
/**** For PWM_mode **************/
#if TIMER0_SELECTION_MODE			==           FAST_PWM_MODE
#define TIMER0_CTC_MODE_PIN_ID					 PIN3
#define TIMER0_CTC_MODE_PORT_ID					 PORTB_ID
#endif
/************* Select the output mode for timer 0 *****************/
#define TIMER0_SELECTION_OUTPUT_COMPARE_MODE     DISCONNECT_MODE
/****** For CTC_mode ***************/
#if TIMER0_SELECTION_OUTPUT_COMPARE_MODE  ==   Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
#define TIMER0_CTC_MODE_PIN_ID				PIN3
#define TIMER0_CTC_MODE_PORT_ID				PORTB_ID
#endif
/***************** Clock select for timer 0********************/
#define TIMER0_CLOCK_SELECT                      CLK_1
/***************************** Interrupt triggered *************/
#define TIMER0_INTERRUPT_TECHNIQE                ENABLE
/************************* For Counter 0*********************************/
#elif SELECTION_MODULE0    		 ==              CONTER0_ENABLE
/******************** Selection edge for counter module ******************/
#define SELECTION_EDGE_COUNTER0    				 FALLAING_EDGE

#endif


/********************For Timer 1*************************************/
#if SELECTION_MODULE1    			 ==  		 TIMER1_ENABLE
/************* Select mode for timer 1 **********************/
#define TIMER1_SELECTION_MODE   	             FAST_PWM_MODE
/**** For PWM_mode **************/
#if TIMER1_SELECTION_MODE			==           FAST_PWM_MODE
/******** Prototype of function use to set the top value in timer 1 ****************/
void TIMER_setTopValue(uint16 top,uint8 select_regsiter);
#define TIMER1_CTC_MODE_PIN_ID				PIN5
#define TIMER1_CTC_MODE_PORT_ID				PORTD_ID
#define USAGE_REG    						USE_ICU_REG_TO_STORE_TOP_VALUE
#endif
/************* Select the output mode for timer 1 ***********/
#define TIMER1_SELECTION_OUTPUT_COMPARE_MODEA    NON_INVERTING_MODE
#define TIMER1_SELECTION_OUTPUT_COMPARE_MODEB    DISCONNECT_MODE
#if TIMER1_SELECTION_OUTPUT_COMPARE_MODEA  ==   Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
#define TIMER1_CTC_MODE_PIN_ID				PIN5
#define TIMER1_CTC_MODE_PORT_ID				PORTD_ID
#endif
#if TIMER1_SELECTION_OUTPUT_COMPARE_MODEB  ==   Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
#define TIMER1B_CTC_MODE_PIN_ID					PIN4
#define TIMER1B_CTC_MODE_PORT_ID				PORTD_ID
#endif
/***************** Clock select for timer 1 *****************/
#define TIMER1_CLOCK_SELECT                      CLK_8
/***************************** Interrupt triggered *************/
#define TIMER1_INTERRUPT_TECHNIQE                DISABLE
/************************* For Counter 1*********************************/
#elif SELECTION_MODULE1     ==                   CONTER1_ENABLE
#define SELECTION_EDGE_COUNTER1                  RAISING_EDGE
/**************** For input capture unit ********************************/
#elif SELECTION_MODULE1            ==            ICU_ENABLE
/******************** Selection edge for input capture unit ************************************/
#define SELECTION_EDGE_ICU  	                 RAISING_EDGE
/***************************** Interrupt triggered *************/
#define ICU1_INTERRUPT_TECHNIQE                  ENABLE
#endif


/***************************For Timer 2********************************/
#if SELECTION_MODULE2       ==                 TIMER2_ENABLE
/************* Select mode for timer 2 **********************/
#define TIMER2_SELECTION_MODE   	           CTC_MODE
/**** For PWM_mode **************/
#if 	TIMER2_SELECTION_MODE			==           FAST_PWM_MODE
#define TIMER2_CTC_MODE_PIN_ID						 PIN7
#define TIMER2_CTC_MODE_PORT_ID						 PORTD_ID
#endif
/************* Select the output mode for timer 2 ***********/
#define TIMER2_SELECTION_OUTPUT_COMPARE_MODE   INVERTING_MODE
#if TIMER2_SELECTION_OUTPUT_COMPARE_MODE  ==   Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
#define TIMER2_CTC_MODE_PIN_ID				PIN7
#define TIMER2_CTC_MODE_PORT_ID				PORTD_ID
#endif
/***************** Clock select for timer 2 ******************/
#define TIMER2_CLOCK_SELECT                    CLK_8
/***************************** Interrupt triggered *************/
#define TIMER2_INTERRUPT_TECHNIQE              ENABLE
/************************* For Counter 2*********************************/
#elif SELECTION_MODULE2          ==            CONTER2_ENABLE
/******************** Selection edge for counter module ******************/
#define SELECTION_EDGE_COUNTER2                RAISING_EDGE
#endif

/*************************   Checking error for modes ***************************/
/****************** For timer 0 *************************/
#if (SELECTION_MODULE0 == TIMER0_ENABLE) && (TIMER0_SELECTION_MODE == NORMAL_MODE) && (TIMER0_SELECTION_OUTPUT_COMPARE_MODE != DISCONNECT_MODE)
#error "The normal mode in the timer0 not has output compare value"
#endif
/****************** For timer 1 *************************/
#if (SELECTION_MODULE1 == TIMER1_ENABLE) && (TIMER1_SELECTION_MODE == NORMAL_MODE) && (TIMER1_SELECTION_OUTPUT_COMPARE_MODE != DISCONNECT_MODE)
#error "The normal mode in the timer1 not has output compare value"
#endif
/****************** For timer 0 *************************/
#if (SELECTION_MODULE2  == TIMER2_ENABLE) && (TIMER2_SELECTION_MODE == NORMAL_MODE) && (TIMER2_SELECTION_OUTPUT_COMPARE_MODE != DISCONNECT_MODE)
#error "The normal mode in the timer2 not has output compare value"
#endif




/*************** Prototype of function to enable timer and select the timer modes *****************/
void iniat_Timer(void);
/*************** Prototype of function to disable timer ***/
uint8 disable_Timer(uint8 timer_selection);
/*** Prototype of SETCALLBACK function *******************/

#if ((SELECTION_MODULE0  == TIMER0_ENABLE) && (TIMER0_SELECTION_MODE != FAST_PWM_MODE)) || ((SELECTION_MODULE1  == TIMER1_ENABLE) && (TIMER1_SELECTION_MODE != FAST_PWM_MODE)) ||((SELECTION_MODULE2  == TIMER2_ENABLE) && (TIMER2_SELECTION_MODE != FAST_PWM_MODE))
#if ((TIMER0_INTERRUPT_TECHNIQE == ENABLE) || (TIMER1_INTERRUPT_TECHNIQE == ENABLE) || (TIMER2_INTERRUPT_TECHNIQE == ENABLE))
uint8 TIMERS_setCallBackFunction(uint8 timer,uint8 mode,uint8 number_of_tick_INT,void (* PointerToFunction)(void));
#endif
#endif
/*** Prototype of function to set the duty cycle for timers ***/
uint8 DUTY_cycleForTimers(uint8 timer,uint16 duty,uint16 pre_load);
#endif
