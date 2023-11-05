#include "../../MCAL/GPIO/gpio.h"
#include "keypad_interface.h"
#include"keypad_config.h"
uint8 KEYPAD_VALUES[ROWSNUM][COLSNUM] =
{
{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'%','0','=','+'}
}; 
void KEYPAD_Init(void)
{
	//cols mode 
	GPIO_setupPinDirection(KEYPAD_PORT,COL0,PIN_OUTPUT);
	GPIO_setupPinDirection(KEYPAD_PORT,COL1,PIN_OUTPUT);
	GPIO_setupPinDirection(KEYPAD_PORT,COL2,PIN_OUTPUT);
	GPIO_setupPinDirection(KEYPAD_PORT,COL3,PIN_OUTPUT);
	// cols value
	GPIO_writePin(KEYPAD_PORT,COL0,LOGIC_HIGH);
	GPIO_writePin(KEYPAD_PORT,COL1,LOGIC_HIGH);
	GPIO_writePin(KEYPAD_PORT,COL2,LOGIC_HIGH);
	GPIO_writePin(KEYPAD_PORT,COL3,LOGIC_HIGH);
	//ROWS mode 
	GPIO_setupPinDirection(KEYPAD_PORT,ROW0,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT,ROW1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT,ROW2,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_PORT,ROW3,PIN_INPUT);
	// ROWS value
	GPIO_writePin(KEYPAD_PORT,ROW0,LOGIC_HIGH);
	GPIO_writePin(KEYPAD_PORT,ROW1,LOGIC_HIGH);
	GPIO_writePin(KEYPAD_PORT,ROW2,LOGIC_HIGH);
	GPIO_writePin(KEYPAD_PORT,ROW3,LOGIC_HIGH);
}
uint8 KEYPAD_Get_Value(void)
{
	uint8 col_count;
	uint8 Row_count;
	uint8 value = '\0';
	for(col_count = COL0; col_count <= COL3; col_count ++)
	{
		GPIO_writePin(KEYPAD_PORT,col_count,LOGIC_LOW);
		for(Row_count = ROW0; Row_count <= ROW3; Row_count ++)
		{
			if(GPIO_readPin(KEYPAD_PORT,Row_count) == PRESSED)
			{
				while(GPIO_readPin(KEYPAD_PORT,Row_count) == PRESSED);
				value = KEYPAD_VALUES[Row_count - ROW0][col_count];
				GPIO_writePin(KEYPAD_PORT,col_count,LOGIC_HIGH);
				return value;
				
			}
		}
		GPIO_writePin(KEYPAD_PORT,col_count,LOGIC_HIGH);
	}
	return value;
}
