#include "interrupt_interface.h"
#include "interrupt_configuration.h"
#include "interrupt_privt.h"
/*******************Calling the module, that contain GPIO functions ********/
#include "../GPIO/gpio.h"
#include "../GPIO/gpio_configuration.h"
/*******************Calling the module, that contain of common macros********/
#include"../../UTILS/common_macro.h"

/***** function that anable and handling the setting to the external interrupt sources: ********/
uint8 ENABLE_externalInterrupt(uint8 select_INT, uint8 select_EDGE)
{
/*************** This variable for checking error*****************/
	uint8 ERROR_STATE = OK;
	if((select_INT <= EXTINT2))
	{

/*********************************************************************/
/************************ FOR EXT0  **********************************/
/*********************************************************************/

		#if                EXT0_SELECTION              ==                ENABLE

			if(select_INT == EXTINT0)
			{
/************************ Set the pin direction *****************************/
			GPIO_setupPinDirection(EXT0_PORT_ID,EXT0_PIN,PIN_INPUT);

		#if    ACTIVE_INTERNAL_PULL_UP_FOR_EXT0        ==                ENABLE

/************************* Active the pull_up resistor: *******************/
			GPIO_writePin(EXT0_PORT_ID,EXT0_PIN,LOGIC_HIGH);
		#endif
/************************* Enable the EX_INT0: *******************/
		SET_BIT(INTERRUPT_ENABLE_REGISTER_EXT0,ENABLE_EXT0_BIT);
/************************* Selection edge : *******************/

			switch(select_EDGE)
			{
			case LOW_LEVEL_EDGE:
				CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT0);
				CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT1);
				break;
			case ANY_LOGIC_CHANGE:
				SET_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT0);
				CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT1);
				break;
			case FALLING_EDGE:
				CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT0);
				SET_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT1);
				break;
			case RISING_EDGE:
				SET_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT0);
				SET_BIT(INTERRUPT_CONTER_REGISTER_EXT0,EXT0_BIT1);
				break;

			}

			}
		#endif

/*********************************************************************/
/************************ FOR EXT1  **********************************/
/*********************************************************************/

		#if                EXT1_SELECTION              ==                ENABLE

			if(select_INT == EXTINT1)
			{
/************************ Set the pin direction *****************************/
			GPIO_setupPinDirection(EXT1_PORT_ID,EXT1_PIN,PIN_INPUT);

		#if    ACTIVE_INTERNAL_PULL_UP_FOR_EXT1        ==                ENABLE

/************************* Active the pull_up resistor: *******************/
			GPIO_writePin(EXT1_PORT_ID,EXT1_PIN,LOGIC_HIGH);
		#endif
/************************* Enable the EX_INT1: *******************/
		SET_BIT(INTERRUPT_ENABLE_REGISTER_EXT1,ENABLE_EXT1_BIT);
/************************* Selection edge : *******************/

		switch(select_EDGE)
		{
		case LOW_LEVEL_EDGE:
			CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT0);
			CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT1);
			break;
		case ANY_LOGIC_CHANGE:
			SET_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT0);
			CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT1);
			break;
		case FALLING_EDGE:
			CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT0);
			SET_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT1);
			break;
		case RISING_EDGE:
			SET_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT0);
			SET_BIT(INTERRUPT_CONTER_REGISTER_EXT1,EXT1_BIT1);
			break;

		}
			}
		#endif


/*********************************************************************/
/************************ FOR EXT2  **********************************/
/*********************************************************************/

		#if                EXT2_SELECTION              ==                ENABLE

			if(select_INT == EXTINT2)
			{
/************************ Set the pin direction *****************************/
			GPIO_setupPinDirection(EXT2_PORT_ID,EXT2_PIN,PIN_INPUT);

		#if    ACTIVE_INTERNAL_PULL_UP_FOR_EXT2        ==                ENABLE

/************************* Active the pull_up resistor: *******************/
			GPIO_writePin(EXT2_PORT_ID,EXT2_PIN,LOGIC_HIGH);
		#endif

/************************* Enable the EX_INT1: *******************/
		SET_BIT(INTERRUPT_ENABLE_REGISTER_EXT2,ENABLE_EXT2_BIT);

/************************* Selection edge : *******************/
			switch(select_EDGE)
			{

				case FALLING_EDGE:
					CLEAR_BIT(INTERRUPT_CONTER_REGISTER_EXT2,EXT2_BIT6);
				break;
				case RISING_EDGE:
					SET_BIT(INTERRUPT_CONTER_REGISTER_EXT2,EXT2_BIT6);
				break;

			}

			}
		#endif
	}
	else
	{
		ERROR_STATE = NOTOK;
	}
	return ERROR_STATE;

	
}
/***************************function that disable the external interrupt sources:******/

uint8 DISABLE_externalInterrupt(uint8 SELECTION_INT)
{
	/*************** This variable for checking error*****************/
		uint8 ERROR_STATE = OK;
		if((SELECTION_INT <= EXTINT2))
		{
			switch(SELECTION_INT)
			{
				case EXTINT0 : CLEAR_BIT(INTERRUPT_ENABLE_REGISTER_EXT0,ENABLE_EXT0_BIT);break;
				case EXTINT1 : CLEAR_BIT(INTERRUPT_ENABLE_REGISTER_EXT1,ENABLE_EXT1_BIT);break;
				case EXTINT2 : CLEAR_BIT(INTERRUPT_ENABLE_REGISTER_EXT2,ENABLE_EXT2_BIT);break;
			}
		}
		else
		{
			ERROR_STATE = NOTOK;
		}
		return ERROR_STATE;

}




/************** Set callback function provided to App****************/
uint8 EXTERNAL_interruptSetCallBack(void (* Local_ptrTOfunc)(void),uint8 select_INT)
{
	/*************** This variable for checking error*****************/
	uint8 ERROR_STATE = OK;
	if((select_INT <= EXTINT2) && (Local_ptrTOfunc != NULL_PTR) )
	{
		/**** Up data the global pointer to function by local pointer to function from APP***/
		ArrPtrToFunction[select_INT] = Local_ptrTOfunc;
	}
	else
	{
		ERROR_STATE = NOTOK;
	}
	return ERROR_STATE;
}
/********* According the pre_build configuration:********************/
#if                EXT0_SELECTION              ==                ENABLE
/************** This is the handler routine for external interrupt zer0********/
void __vector_1(void)           __attribute__((signal));
void __vector_1(void)
{
	/* To avoid the willed pointer or dereference to garbage address*/
	if(ArrPtrToFunction[EXTINT0] != NULL_PTR)
	{
		(* ArrPtrToFunction[EXTINT0])();
	}

}
#endif
/********* According the pre_build configuration:********************/
#if                EXT1_SELECTION              ==                ENABLE
/************** This is the handler routine for external interrupt one ********/
void __vector_2(void)           __attribute__((signal));
void __vector_2(void)
{
	/* To avoid the willed pointer or dereference to garbage address*/
	if(ArrPtrToFunction[EXTINT1] != NULL_PTR)
	{
		(* ArrPtrToFunction[EXTINT1])();
	}
}
#endif
/********* According the pre_build configuration:********************/
#if                EXT2_SELECTION              ==                 ENABLE
/************** This is the handler routine for external interrupt two********/
void __vector_3(void)           __attribute__((signal));
void __vector_3(void)
{
	/* To avoid the willed pointer or dereference to garbage address*/
	if(ArrPtrToFunction[EXTINT2] != NULL_PTR)
	{
		 ArrPtrToFunction[EXTINT2]();
	}
}
#endif
