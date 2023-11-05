#ifndef KAYPAD_CONFIG_H
#define KAYPAD_CONFIG_H
#include "../../MCAL/GPIO/gpio_configuration.h"
#define KEYPAD_PORT PORTC_ID

#define COL0 PIN0
#define COL1 PIN1
#define COL2 PIN2
#define COL3 PIN3

#define ROW0 PIN4
#define ROW1 PIN5
#define ROW2 PIN6
#define ROW3 PIN7

#define ROWSNUM 4
#define COLSNUM 4

#define PRESSED 0
#define NOTPRESSED 1
#endif
