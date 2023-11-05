#ifndef TIMER_CONFIGURATION_H
#define TIMER_CONFIGURATION_H
/******	Number of usage timers in application *******/
#define TIMERS_NUMBERS   		  3
/****** Maximum modes in each timer *************************/
#define TIMERS_MAX_NUMBER_MODES   3
/********************* Timer select *************************/
#define Timer0 				0
#define Timer1 				1 // 16 bit register
#define Timer2 				2
#define TIMER0_ENABLE		10
#define TIMER1_ENABLE		20
#define TIMER2_ENABLE		30
#define ICU_ENABLE			40
/********************* Timer modes ************************/
#define NORMAL_MODE 				0
#define PHASE_CORRECT_MODE 			1
#define CTC_MODE 					2
#define FAST_PWM_MODE 				3
#define CTC_MODE_ICU				5
/********************* Mode of external pin OCX **************/
#define DISCONNECT_MODE                                   0
#define Toggle_OCx_on_compare_match_IN_CTC_Mode_only_OR_Reserved  1

/********************** Duty cycle modes *************************/
#define NON_INVERTING_MODE 			2
#define INVERTING_MODE 				3

/****************** Clock select *************************/

#define NO_CLK_SOURSE 0
#define CLK_1         1
#define CLK_8         8
#define CLK_64        64
#define CLK_256       256
#define CLK_1024      1024
/******************* Selection edge in counter mode *************/
#define External_clock_source_T0_pin_ClocK_falling _edge 	6
#define External_clock_source_T0_pin_ClocK_rising _edge 	7
/******************* Bits of control register for Timer0 *******/
#define TIMER0_CTC_ACTIVE_BIT        7
#define TIMER0_WAVEFORM_BIT0     	 6
#define TIMER0_WAVEFORM_BIT1     	 3
#define TIMER0_OUTPUT_MODE_BIT0 	 4
#define TIMER0_OUTPUT_MODE_BIT1 	 5
#define TIMER0_CLOCK_SELECT_BIT0     0
#define TIMER0_CLOCK_SELECT_BIT1     1
#define TIMER0_CLOCK_SELECT_BIT2     2


/******************* Bits of control register A for Timer1 *******/
#define TIMER1_CTC_ACTIVE_BITA			3
#define TIMER1_CTC_ACTIVE_BITB          2
#define TIMER1_WAVEFORM_BIT10			0
#define TIMER1_WAVEFORM_BIT11     	 	1
#define TIMER1_OUTPUT_MODE_BITA0 	 	6
#define TIMER1_OUTPUT_MODE_BITA1 	 	7
#define TIMER1_OUTPUT_MODE_BITB0 	 	4
#define TIMER1_OUTPUT_MODE_BITB1 	 	5
/******************* Bits of control register B for Timer1 *******/

#define TIMER1_INPUT_CAPTURE_EDGE_SELECT_BIT 		6
#define TIMER1_WAVEFORM_BIT12     	 				3
#define TIMER1_WAVEFORM_BIT13     	 				4
#define TIMER1_CLOCK_SELECT_BIT0     				0
#define TIMER1_CLOCK_SELECT_BIT1     				1
#define TIMER1_CLOCK_SELECT_BIT2     				2
/******************* Bits of control register for Timer2 *******/

#define TIMER2_CTC_ACTIVE_BIT        	7
#define TIMER2_WAVEFORM_BIT0     	 	6
#define TIMER2_WAVEFORM_BIT1     	 	3
#define TIMER2_OUTPUT_MODE_BIT0 	 	4
#define TIMER2_OUTPUT_MODE_BIT1 	 	5
#define TIMER2_CLOCK_SELECT_BIT0     	0
#define TIMER2_CLOCK_SELECT_BIT1     	1
#define TIMER2_CLOCK_SELECT_BIT2     	2


/************************ Mask register for enable the interrupt *************************/
/******************** For TIMER0 ************************/
/***************  Overflow Interrupt Enable *************/
#define TIMER0_OVERFLOW_ENABLE_BIT          0
/***************  Output compare mode Interrupt Enable *************/
#define TIMER0_OUTPUTCOMPARE_ENABLE_BIT     1
/******************** For TIMER2 ************************/
/***************  Overflow Interrupt Enable *************/
#define TIMER2_OVERFLOW_ENABLE_BIT          6
/***************  Output compare mode Interrupt Enable *************/
#define TIMER2_OUTPUTCOMPARE_ENABLE_BIT     7
/******************** For TIMER1 ************************/
/***************  Overflow Interrupt Enable *************/
#define TIMER1_OVERFLOW_ENABLE_BIT          2
/***************  Output compare mode Interrupt Enable *************/
#define TIMER1A_OUTPUTCOMPARE_ENABLE_BIT    4
#define TIMER1B_OUTPUTCOMPARE_ENABLE_BIT    3
/********************** Input capture unit interrupt enable ***************************/
#define TIMER1_INPUT_CAPTURE_ENABLE_BIT     5


/************************ Flags register for enable the interrupt *************************/
/******************** For TIMER0 ************************/
/***************  Overflow Interrupt Flag *************/
#define TIMER0_OVERFLOW_FLAG_BIT            0
/***************  Output compare mode Interrupt Enable *************/
#define TIMER0_OUTPUTCOMPARE_FLAG_BIT       1
/******************** For TIMER2 ************************/
/***************  Overflow Interrupt Enable *************/
#define TIMER2_OVERFLOW_FLAG_BIT          	6
/***************  Output compare mode Interrupt Enable *************/
#define TIMER2_OUTPUTCOMPARE_FLAG_BIT     	7
/******************** For TIMER1 ************************/
/***************  Overflow Interrupt Enable *************/
#define TIMER1_OVERFLOW_FLAG_BIT          	2
/***************  Output compare mode Interrupt Enable *************/
#define TIMER1A_OUTPUTCOMPARE_FLAG_BIT    	4
#define TIMER1B_OUTPUTCOMPARE_FLAG_BIT    	3
/********************** Input capture unit interrupt enable ***************************/
#define TIMER1_INPUT_CAPTURE_FLAG_BIT     	5
/********************* Interrupt service routine for each source ************************/
#define TIMER_OVERFLOW_MODE 				0
#define TIMER_CTC_MODE 						1
#define TIMER1_ICU						 	3
#define USE_ICU_REG_TO_STORE_TOP_VALUE      1
#define USE_OCR1A_REG_TO_STORE_TOP_VALUE    0
#endif
