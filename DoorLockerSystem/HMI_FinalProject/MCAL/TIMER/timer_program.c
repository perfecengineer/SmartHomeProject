#include "timer_interface.h"
#include "timer_registers.h"
#include "../GPIO/gpio.h"
#include "../../UTILS/common_macro.h"
#if ((SELECTION_MODULE0  == TIMER0_ENABLE) && (TIMER0_SELECTION_MODE != FAST_PWM_MODE)) || ((SELECTION_MODULE1  == TIMER1_ENABLE) && (TIMER1_SELECTION_MODE != FAST_PWM_MODE)) ||((SELECTION_MODULE2  == TIMER2_ENABLE) && (TIMER2_SELECTION_MODE != FAST_PWM_MODE))
#if ((TIMER0_INTERRUPT_TECHNIQE == ENABLE) || (TIMER1_INTERRUPT_TECHNIQE == ENABLE) || (TIMER2_INTERRUPT_TECHNIQE == ENABLE))
/*** Array for timers modes and set call back function***/
static void (* TimersModes[TIMERS_NUMBERS][TIMERS_MAX_NUMBER_MODES])(void);
/*** Array to store number of interrupts***/
static uint8 ArrayOfTickTimesInterrupt[TIMERS_NUMBERS][TIMERS_MAX_NUMBER_MODES] = {{0,0}};
/*** Array to store the counts the interrupts for each timer ***/
static uint8 Counter[TIMERS_NUMBERS] = {0};
#endif
#endif
void iniat_Timer(void)
{
/*************  For timer 0 ****************************/
#if SELECTION_MODULE0	         	==			TIMER0_ENABLE

/************* Select mode for timer 0 ****************************/
	#if 	TIMER0_SELECTION_MODE   ==	NORMAL_MODE
/*************** Enable interrupt for overflow mode for timer 0*******/

				SET_BIT(CONTROL_REG_TIMER0,TIMER0_CTC_ACTIVE_BIT);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT1);
				#if TIMER0_INTERRUPT_TECHNIQE       ==      ENABLE
				/*************** Enable interrupt for overflow mode for timer 0 ***/
					SET_BIT(MASKABLE_REG_TIMERS,TIMER0_OVERFLOW_ENABLE_BIT);
				#endif
	#elif	TIMER0_SELECTION_MODE   ==	PHASE_CORRECT_MODE
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT1);
	#elif	TIMER0_SELECTION_MODE   ==	CTC_MODE
				#if TIMER0_INTERRUPT_TECHNIQE       ==      ENABLE
				/*************** Enable interrupt for overflow mode for timer 0 ***/
					SET_BIT(MASKABLE_REG_TIMERS,TIMER0_OUTPUTCOMPARE_ENABLE_BIT);
				#endif
				// To force the ctc mode :
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_CTC_ACTIVE_BIT);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT0);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT1);

	#elif	TIMER0_SELECTION_MODE   ==	FAST_PWM_MODE
				DATA_REG_TIMER0 = 0;
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CTC_ACTIVE_BIT);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT0);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_WAVEFORM_BIT1);
	#endif

/************* Select the output mode for timer 0 ****************************/

	#if 	TIMER0_SELECTION_OUTPUT_COMPARE_MODE   ==	DISCONNECT_MODE
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT1);
	#elif 	TIMER0_SELECTION_OUTPUT_COMPARE_MODE   ==	Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
				GPIO_setupPinDirection(TIMER0_CTC_MODE_PORT_ID,TIMER0_CTC_MODE_PIN_ID,PIN_OUTPUT);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT1);
	#elif 	TIMER0_SELECTION_OUTPUT_COMPARE_MODE   ==	NON_INVERTING_MODE
				GPIO_setupPinDirection(TIMER0_CTC_MODE_PORT_ID,TIMER0_CTC_MODE_PIN_ID,PIN_OUTPUT);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT0);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT1);
	#elif 	TIMER0_SELECTION_OUTPUT_COMPARE_MODE   ==	INVERTING_MODE
				GPIO_setupPinDirection(TIMER0_CTC_MODE_PORT_ID,TIMER0_CTC_MODE_PIN_ID,PIN_OUTPUT);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT0);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_OUTPUT_MODE_BIT1);
	#endif
/************* Select the Clock of timer 0 ****************************/

	#if 	TIMER0_CLOCK_SELECT		==		NO_CLK_SOURSE
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);
	#elif 	TIMER0_CLOCK_SELECT		==		CLK_1
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);
	#elif 	TIMER0_CLOCK_SELECT		==		CLK_8
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);
	#elif 	TIMER0_CLOCK_SELECT		==		CLK_64
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);

	#elif 	TIMER0_CLOCK_SELECT		==		CLK_256
			CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
			CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);
	#elif 	TIMER0_CLOCK_SELECT		==		CLK_1024
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
			CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);

	#endif
/************************************* for counter 0 **************************************************/
#elif SELECTION_MODULE0     ==     CONUTER0_ENABLE
/****************************** For falling edge ******************************************************/
		#if			SELECTION_EDGE_COUNTER0   		==	  FALLAING_EDGE
			CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);
/********************************* For raising edge ******************************************************/
		#elif		SELECTION_EDGE_COUNTER0 	  ==		RAISING_EDGE
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
			SET_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);
	#endif

#endif


/************************ timer 1 ****************************/
#if SELECTION_MODULE1               ==     TIMER1_ENABLE
/************* Select mode for timer 1 ********************************/
	#if 	TIMER1_SELECTION_MODE   ==	NORMAL_MODE
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITA);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITB);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT10);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT11);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT12);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT13);
				#if TIMER1_INTERRUPT_TECHNIQE       ==      ENABLE
				/*************** Enable interrupt for overflow mode for timer 1 ***/
					SET_BIT(MASKABLE_REG_TIMERS,TIMER1_OVERFLOW_ENABLE_BIT);
				#endif
	#elif	TIMER1_SELECTION_MODE   ==	PHASE_CORRECT_MODE
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT10);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT11);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT12);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT13);
	#elif	TIMER1_SELECTION_MODE   ==	CTC_MODE
				// To force the ctc mode :
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITA);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT10);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT11);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT12);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT13);
				#if TIMER1_INTERRUPT_TECHNIQE       ==      ENABLE
				/*************** Enable interrupt for overflow mode for timer 0 ***/
					SET_BIT(MASKABLE_REG_TIMERS,TIMER1A_OUTPUTCOMPARE_ENABLE_BIT);
				#endif
	#elif	TIMER1_SELECTION_MODE   		==			CTC_MODE_B
				// To force the ctc mode :

				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITB);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT10);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT11);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT12);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT13);
				#if TIMER1_INTERRUPT_TECHNIQE       ==      ENABLE
				/*************** Enable interrupt for overflow mode for timer 0 ***/
					SET_BIT(MASKABLE_REG_TIMERS,TIMER1B_OUTPUTCOMPARE_ENABLE_BIT);
				#endif
	#elif	(TIMER1_SELECTION_MODE == FAST_PWM_MODE) && (USAGE_REG == USE_ICU_REG_TO_STORE_TOP_VALUE)
				GPIO_setupPinDirection(TIMER1_CTC_MODE_PORT_ID,TIMER1_CTC_MODE_PIN_ID,PIN_OUTPUT);
			// To force the ctc mode :
				DATA_REG_TIMER1 = 0;
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITA);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITB);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT10);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT11);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT12);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT13);
	#elif	(TIMER1_SELECTION_MODE == FAST_PWM_MODE) && (USAGE_REG == USE_OCR1B_REG_TO_STORE_TOP_VALUE)
				DATA_REG_TIMER1 = 0;
				// To force the ctc mode :
				GPIO_setupPinDirection(TIMER1_CTC_MODE_PORT_ID,TIMER1_CTC_MODE_PIN_ID,PIN_OUTPUT);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITA);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_CTC_ACTIVE_BITB);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT10);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_WAVEFORM_BIT11);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT12);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_WAVEFORM_BIT13);


	#endif
/************* Select the output mode for timer 1 for register OCR1_A ****************************/

	#if 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEA   ==	DISCONNECT_MODE
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA0);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA1);
	#elif 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEA   ==	Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
				GPIO_setupPinDirection(TIMER1_CTC_MODE_PORT_ID,TIMER1_CTC_MODE_PIN_ID,PIN_OUTPUT);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA0);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA1);
	#elif 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEA   ==	NON_INVERTING_MODE
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA0);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA1);
	#elif 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEA   ==	INVERTING_MODE
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA0);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITA1);

	#endif
/************* Select the output mode for timer 1 for register OCR1_B ****************************/
	#if 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEB   ==	DISCONNECT_MODE
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB0);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB1);
	#elif 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEB   ==	Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB0);
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB1);
	#elif 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEB   ==	NON_INVERTING_MODE
				CLEAR_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB0);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB1);
	#elif 	TIMER1_SELECTION_OUTPUT_COMPARE_MODEB   ==	INVERTING_MODE
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB0);
				SET_BIT(CONTROL_REG_TIMER1A,TIMER1_OUTPUT_MODE_BITB1);

	#endif

	#if 	TIMER1_CLOCK_SELECT		==		NO_CLK_SOURSE
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);
	#elif 	TIMER1_CLOCK_SELECT		==		CLK_1
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);
	#elif 	TIMER1_CLOCK_SELECT		==		CLK_8
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);
	#elif 	TIMER1_CLOCK_SELECT		==		CLK_64
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);

	#elif 	TIMER1_CLOCK_SELECT		==		CLK_256
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);
	#elif 	TIMER1_CLOCK_SELECT		==		CLK_1024
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);

	#endif



/************************************* for counter 1 **************************************************/
#elif SELECTION_MODULE1     ==    ICU_ENABLE
/****************************** For falling edge ******************************************************/
		#if		SELECTION_EDGE_COUNTER1   		==	  FALLAING_EDGE
						CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
						SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
						SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);
/********************************* For raising edge ******************************************************/
		#elif	SELECTION_EDGE_COUNTER1 	  ==		RAISING_EDGE
						SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
						SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
						SET_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);
		#endif

/************************************* for input capture unit  **************************************************/
#elif SELECTION_MODULE1     ==    ICU_ENABLE
/****************************** For falling edge ******************************************************/
	#if		SELECTION_EDGE_ICU   		==	  FALLAING_EDGE
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_INPUT_CAPTURE_EDGE_SELECT_BIT);

/********************************* For raising edge ******************************************************/
	#elif	SELECTION_EDGE_ICU 	  ==		RAISING_EDGE
				SET_BIT(CONTROL_REG_TIMER1B,TIMER1_INPUT_CAPTURE_EDGE_SELECT_BIT);

	#endif




#endif


/*********************** For timer 2 ****************************/
#if SELECTION_MODULE2                ==         TIMER2_ENABLE
/****************** Select mode for timer 2 ****************************/
	#if 	TIMER2_SELECTION_MODE   ==	NORMAL_MODE
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CTC_ACTIVE_BIT);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT1);
				#if TIMER2_INTERRUPT_TECHNIQE       ==      ENABLE
				/*************** Enable interrupt for overflow mode for timer 0 ***/
					SET_BIT(MASKABLE_REG_TIMERS,TIMER2_OVERFLOW_ENABLE_BIT);
				#endif
	#elif	TIMER2_SELECTION_MODE   ==	PHASE_CORRECT_MODE
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT1);
	#elif	TIMER2_SELECTION_MODE   ==	CTC_MODE
/********************* To force the ctc mode ****************/
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CTC_ACTIVE_BIT);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT1);
				#if TIMER2_INTERRUPT_TECHNIQE       ==      ENABLE
				/*************** Enable interrupt for overflow mode for timer 0 ***/
					SET_BIT(MASKABLE_REG_TIMERS,TIMER2_OUTPUTCOMPARE_ENABLE_BIT);
				#endif
	#elif	TIMER2_SELECTION_MODE   ==	FAST_PWM_MODE
				DATA_REG_TIMER2 = 0;
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CTC_ACTIVE_BIT);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_WAVEFORM_BIT1);
	#endif
/***************** Select the output mode for timer 2 ****************************/
	#if 	TIMER2_SELECTION_OUTPUT_COMPARE_MODE   ==	DISCONNECT_MODE
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT1);
	#elif 	TIMER2_SELECTION_OUTPUT_COMPARE_MODE   ==	Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved
				GPIO_setupPinDirection(TIMER2_CTC_MODE_PORT_ID,TIMER2_CTC_MODE_PIN_ID,PIN_OUTPUT);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT1);
	#elif 	TIMER2_SELECTION_OUTPUT_COMPARE_MODE   ==	NON_INVERTING_MODE
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT1);
	#elif 	TIMER2_SELECTION_OUTPUT_COMPARE_MODE   ==	INVERTING_MODE
			SET_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT0);
			SET_BIT(CONTROL_REG_TIMER2,TIMER2_OUTPUT_MODE_BIT1);
	#endif
/***************** Select the Clock of timer 2 ****************************/
	#if 	TIMER2_CLOCK_SELECT		==		NO_CLK_SOURSE
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);
	#elif 	TIMER2_CLOCK_SELECT		==		CLK_1
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);
	#elif 	TIMER2_CLOCK_SELECT		==		CLK_8
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);
	#elif 	TIMER2_CLOCK_SELECT		==		CLK_64
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);

	#elif 	TIMER2_CLOCK_SELECT		==		CLK_256
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);
	#elif 	TIMER2_CLOCK_SELECT		==		CLK_1024
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);

	#endif


/************************************* for counter 2 **************************************************/
#elif SELECTION_MODULE2     ==     COUNTER2_ENABLE
/****************************** For falling edge ******************************************************/
	#if		SELECTION_EDGE_COUNTER2   		==	  FALLAING_EDGE
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);
/********************************* For raising edge ******************************************************/
#elif		SELECTION_EDGE_COUNTER2 	  ==		RAISING_EDGE
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				SET_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);
					#endif
#endif
}
uint8 disable_Timer(uint8 timer_selection)
{
	uint8 ERROR_STATE = OK;
	switch(timer_selection)
	{
/****************** To disable timer 0, clear the clock source *************/
	case Timer0:
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER0,TIMER0_CLOCK_SELECT_BIT2);
	break;
/****************** To disable timer 1, clear the clock source *************/
	case Timer1:
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER1B,TIMER1_CLOCK_SELECT_BIT2);
	break;
/****************** To disable timer 2, clear the clock source *************/
	case Timer2:
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT0);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT1);
				CLEAR_BIT(CONTROL_REG_TIMER2,TIMER2_CLOCK_SELECT_BIT2);
	break;
/************* For error state *********************/
	default:ERROR_STATE = NOTOK;

	}

	return ERROR_STATE;
}

/********* Set duty for timers ************************/
uint8 DUTY_cycleForTimers(uint8 timer,uint16 duty,uint16 pre_load)
{
	uint8 Error_state = NOTOK;

	if(timer >= Timer0 && timer <= Timer1)
	{
		switch(timer)
		{
		case Timer0:
#if SELECTION_MODULE0				==			 TIMER0_ENABLE
#if TIMER0_SELECTION_MODE			!=           NORMAL_MODE
			OUTPUT_COMPARE_REG_TIMER0 = duty;
#endif
#if TIMER0_SELECTION_MODE			!=           FAST_PWM_MODE
		DATA_REG_TIMER0 = pre_load;
#endif
#endif
		break;
		case Timer1:
#if SELECTION_MODULE1				==			 TIMER1_ENABLE
#if TIMER1_SELECTION_MODE			!=           NORMAL_MODE
			OUTPUT_COMPARE_REG_TIMER1A = duty;
#endif
#if TIMER1_SELECTION_MODE			!=           FAST_PWM_MODE
			DATA_REG_TIMER1 = pre_load;
#endif
#endif
		break;
		case Timer2:
#if SELECTION_MODULE2				==			 TIMER2_ENABLE
#if TIMER2_SELECTION_MODE			!=           NORMAL_MODE
			OUTPUT_COMPARE_REG_TIMER2 = duty;
#endif
#if TIMER2_SELECTION_MODE			!=           FAST_PWM_MODE
		DATA_REG_TIMER2 = pre_load;
#endif
#endif
		break;
		}
		Error_state = OK;
	}
	return Error_state;
}
#if ((SELECTION_MODULE0  == TIMER0_ENABLE) && (TIMER0_SELECTION_MODE != FAST_PWM_MODE)) || ((SELECTION_MODULE1  == TIMER1_ENABLE) && (TIMER1_SELECTION_MODE != FAST_PWM_MODE)) ||((SELECTION_MODULE2  == TIMER2_ENABLE) && (TIMER2_SELECTION_MODE != FAST_PWM_MODE))
#if ((TIMER0_INTERRUPT_TECHNIQE == ENABLE) || (TIMER1_INTERRUPT_TECHNIQE == ENABLE) || (TIMER2_INTERRUPT_TECHNIQE == ENABLE))
/*** Implementation of SETCALLBACK function *******************/
uint8 TIMERS_setCallBackFunction(uint8 timer,uint8 mode,uint8 NumerOfTickTimes,void (* PointerToFunction)(void))
{
/****************** For error state checking ******************************/
	uint8 ErrorStateVariable = NOTOK;
	if((timer >= Timer0 && timer <= Timer2) && (timer >= TIMER_OVERFLOW_MODE && timer <= TIMER1_ICU) && (PointerToFunction != NULL_PTR))
	{
/******* Assign array of pointers to functions with address of input function according input timer and mode ***/
		TimersModes[timer][mode] = PointerToFunction;
/******* Set value of number of times of interrupt *************************************************************/
		ArrayOfTickTimesInterrupt[timer][mode] = NumerOfTickTimes;
/******* Set the error state variable with okay *************************************/
		ErrorStateVariable = OK;
	}
	return ErrorStateVariable;
}
#endif
#endif
/********************* For ISR of timer 0 ********/
#if SELECTION_MODULE0			==		TIMER0_ENABLE
#if TIMER0_INTERRUPT_TECHNIQE   ==    	ENABLE
/*** ISR for each  mode in timer 0 ********/
#if TIMER0_SELECTION_MODE		==		NORMAL_MODE

void __vector_11(void)         __attribute__((signal));
void __vector_11(void)
{
	Counter[Timer0] ++;
	if(ArrayOfTickTimesInterrupt[Timer0][TIMER_OVERFLOW_MODE])
	{
		/*********** Check the number of interrupts to execute the required function *******************************/
			if(Counter[Timer0] == ArrayOfTickTimesInterrupt[Timer0][TIMER_OVERFLOW_MODE])
			{
				if((* TimersModes[Timer0][TIMER_OVERFLOW_MODE]) != NULL_PTR)
				{
					(* TimersModes[Timer0][TIMER_OVERFLOW_MODE])();
					Counter[Timer0] = 0;
				}
			}
	}


}
#elif TIMER0_SELECTION_MODE		==		CTC_MODE
void __vector_10(void)            __attribute__((signal));
void __vector_10(void)
{
	Counter[Timer0] ++;
	if(ArrayOfTickTimesInterrupt[Timer0][CTC_MODE])
	{
		/*********** Check the number of interrupts to execute the required function *******************************/
			if(Counter[Timer0] == ArrayOfTickTimesInterrupt[Timer0][CTC_MODE])
			{
				if((* TimersModes[Timer0][CTC_MODE]) != NULL_PTR)
				{
					(* TimersModes[Timer0][CTC_MODE])();
					Counter[Timer0] = 0;
				}
			}
	}
}
#endif
#endif
#endif
/********************* For ISR of timer 1 ****************/
#if SELECTION_MODULE1			   ==	 		TIMER1_ENABLE
#if TIMER1_SELECTION_MODE		   ==           FAST_PWM_MODE
/******** Implementation of function use to set the top value in timer 1 ****************/
void TIMER_setTopValue(uint16 top,uint8 select_regsiter)
{
	if(select_regsiter)
	{
		INPUT_CAPTURE_REGISTER_TIMER1 = top;
	}
	else
	{
		OUTPUT_COMPARE_REG_TIMER1A = top;
	}
}
/************** ISR for timer 1 modes ********************/
#endif
#if TIMER1_INTERRUPT_TECHNIQE      ==    ENABLE
#if TIMER1_SELECTION_MODE		   ==	 NORMAL_MODE

void __vector_9(void)         __attribute__((signal));
void __vector_9(void)
{
	Counter[Timer1] ++;
	if(ArrayOfTickTimesInterrupt[Timer1][TIMER_OVERFLOW_MODE])
	{
		/*********** Check the number of interrupts to execute the required function *******************************/
			if(Counter[Timer1] == ArrayOfTickTimesInterrupt[Timer1][TIMER_OVERFLOW_MODE])
			{
				if((* TimersModes[Timer1][TIMER_OVERFLOW_MODE]) != NULL_PTR)
				{
					(* TimersModes[Timer1][TIMER_OVERFLOW_MODE])();
					Counter[Timer1] = 0;
				}
			}
	}


}
#elif TIMER1_SELECTION_MODE		==		CTC_MODE
void __vector_7(void)            __attribute__((signal));
void __vector_7(void)
{
	Counter[Timer1] ++;
	if(ArrayOfTickTimesInterrupt[Timer1][CTC_MODE])
	{
		/*********** Check the number of interrupts to execute the required function *******************************/
			if(Counter[Timer1] == ArrayOfTickTimesInterrupt[Timer1][CTC_MODE])
			{
				if((* TimersModes[Timer1][CTC_MODE]) != NULL_PTR)
				{
					(* TimersModes[Timer1][CTC_MODE])();
					Counter[Timer1] = 0;
				}
			}
	}
}
#endif
#endif
#endif
/********************* For ISR of timer 2  modes ********/
#if SELECTION_MODULE2			==		TIMER2_ENABLE
#if TIMER2_INTERRUPT_TECHNIQE   == 	    ENABLE
#if TIMER2_SELECTION_MODE		==		NORMAL_MODE
/*********** Enable the interrupt for overflow mode in timer 0***/

void __vector_5(void)         __attribute__((signal));
void __vector_5(void)
{
	Counter[Timer2] ++;
	if(ArrayOfTickTimesInterrupt[Timer2][TIMER_OVERFLOW_MODE])
	{
		/*********** Check the number of interrupts to execute the required function *******************************/
			if(Counter[Timer2] == ArrayOfTickTimesInterrupt[Timer2][TIMER_OVERFLOW_MODE])
			{
				if((* TimersModes[Timer2][TIMER_OVERFLOW_MODE]) != NULL_PTR)
				{
					(* TimersModes[Timer2][TIMER_OVERFLOW_MODE])();
					Counter[Timer2] = 0;
				}
			}
	}




}
#elif TIMER2_SELECTION_MODE		==		CTC_MODE
void __vector_4(void)            __attribute__((signal));
void __vector_4(void)
{
	Counter[Timer2] ++;
	if(ArrayOfTickTimesInterrupt[Timer2][CTC_MODE])
	{
		/*********** Check the number of interrupts to execute the required function *******************************/
			if(Counter[Timer2] == ArrayOfTickTimesInterrupt[Timer2][CTC_MODE])
			{
				if((* TimersModes[Timer2][CTC_MODE]) != NULL_PTR)
				{
					(* TimersModes[Timer2][CTC_MODE])();
					Counter[Timer2] = 0;
				}
			}
	}


}
#endif
#endif
#endif
