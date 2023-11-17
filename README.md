Project Title: Smart Home System with Four Subsystems using Atmega32 Microcontrollers

Project Description:

The Smart Home System is an embedded system project designed to provide automation and control for various aspects of a home, enhancing convenience, comfort, and energy efficiency. This project utilizes Atmega32 microcontrollers to create four distinct subsystems, each responsible for different tasks within the smart home environment. These subsystems are as follows:

1. Door Locker Subsystem:

Hardware Components: Two Atmega32 microcontrollers (MCUs), Keypad, LCD, Ultrasonic Sensor, Door Mechanism, and External EEPROM.
Communication: The master node communicates with the slave node using the Serial Peripheral Interface (SPI) protocol.
Functionality:
The master node receives password input from the user via the keypad, LCD, or a virtual terminal.
It communicates with the slave node to handle the door locking/unlocking mechanism.
The distance from an ultrasonic sensor is used to determine if a person is approaching the door.
The slave node accesses an external EEPROM using the I2C protocol to read and write passwords securely.
- SoftWare Architecture Layers:
	.Master Node:
	 	APP   -> main + SW components.
		HAL   -> KEYPAD + LCD + LED + ULTRA_SONIC_SENSOR.
		MCAL  -> GPIO + GLOBAL_INTERRUPT + ICU + TIMER + UART + SPI + WDT.
		UTILS -> STD_TYPES + COMM_MACROS
	.Slave Node:
	 	APP   -> main + SW components.
		HAL   -> ALARM + DC_MOTOR + EX_EEPROM + LCD + LED + SERVO_MOTOR + STEPPER_MOTOR.
		MCAL  -> GPIO + TIMER(PWM) + UART + SPI + TWI + WDT.
		UTILS -> STD_TYPES + COMM_MACROS

2. Reception System Subsystem:

Hardware Components: Atmega32 MCU, LM35 Temperature Sensor,LCD,Fan, Heater.
Functionality:
Monitors the temperature using the LM35 sensor.
Controls the fan and heater speed to maintain a comfortable temperature in the reception area.
- SoftWare Architecture Layers:
	 	APP   -> main + SW components.
		HAL   -> DC_MOTOR + LCD + LM35_TEMP_SENSOR.
		MCAL  -> GPIO + GLOBAL_INTERRUPT + EX_INTERRUPT + TIMER(PWM) + ADC + UART.
		UTILS -> STD_TYPES + COMM_MACROS
			
3. Room System Subsystem:

Hardware Components: Atmega32 MCU, Ultrasonic Sensor, LM35 Temperature Sensor, Fan,LCD, Heater, Room Door.
Functionality:
Monitors the distance of individuals approaching the room using an ultrasonic sensor.
Monitors the temperature using the LM35 sensor.
Controls the room door, opening or closing it based on the presence of individuals.
Adjusts the fan and heater speed to maintain a comfortable temperature in the room.
- SoftWare Architecture Layers:
	 	APP   -> main + SW components.
		HAL   -> DC_MOTOR + LCD + LM35_TEMP_SENSOR + ULTRA_SONIC_SENSOR.
		MCAL  -> GPIO + GLOBAL_INTERRUPT + EX_INTERRUPT + TIMER(PWM) + ADC + ICU.
		UTILS -> STD_TYPES + COMM_MACROS
		
4. Home's Lighting System Subsystem:

Hardware Components: Atmega32 MCU, LCD,Two LDR Sensors (Light-Dependent Resistors), Lighting Control System.
Functionality:
Measures the light intensity in the reception area and the room using LDR sensors.
Adjusts the lighting intensity accordingly to optimize energy usage and create a comfortable environment.
Common Features:

All MCUs in the subsystems are Atmega32 microcontrollers.
Communication between the subsystems may be facilitated using UART, I2C, and SPI protocols.
The system provides a user-friendly interface through keypads, LCDs, and virtual terminals.
The system enhances security by managing door access through password authentication and ultrasonic sensing.
The system provides energy-efficient climate control with temperature sensors and fan/heater control.
The system offers adaptive lighting to create the desired ambiance and conserve energy.

- SoftWare Architecture Layers:
	 	APP   -> main + SW components.
		HAL   -> LCD + LDR.
		MCAL  -> GPIO + GLOBAL_INTERRUPT + EX_INTERRUPT + TIMER(PWM) + ADC.	 
		UTILS -> STD_TYPES + COMM_MACROS
