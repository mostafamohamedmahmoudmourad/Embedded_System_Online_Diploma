/*
 * main.c
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */
 
#include <stdint.h>
#include <stdio.h>
#include "driver.h"
#include "MainAlg.h"
#include "AlarmMonitor.h"
#include "AlarmActuatorDriver.h"
#include "PressureSensorDriver.h"

void setup()
{
	AlarmActuatorDriver_init();  									  // Initialize the alarm actuator driver
	PressureSensorDriver_state = STATE(PressureSensorDriver_reading);   // Set the initial state for the alarm actuator driver
	MainAlg_state = STATE(MainAlg_high_pressure_delection);  		  // Set the initial state for the main algorithm
	AlarmMonitor_state = STATE(AlarmMonitor_alarmOff); 		 		  // Set the initial state for the alarm monitor
	StopAlarm();  													  // Ensure the alarm is off at the start
}

int main()
{
	//GPIO_INITIALIZATION();  // Initialize the GPIOs
	//GPIOA_BRR = 0x8000;
	setup();  // Call the setup function to initialize states and drivers

	while (1)  // Main loop
	{
		PressureSensorDriver_state();  		// Execute the current state of the alarm actuator driver
		MainAlg_state();  					// Execute the current state of the main algorithm
		AlarmMonitor_state();  				// Execute the current state of the alarm monitor
	}
}
