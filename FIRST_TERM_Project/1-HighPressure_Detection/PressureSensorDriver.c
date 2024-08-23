/*
 * PressureSensorDriver.c
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#include "PressureSensorDriver.h"

static int PressureSensorDriver_pVal = 0;  // Variable to store the pressure sensor value

void (* PressureSensorDriver_state)();  // Function pointer to the current state function



void PressureSensorDriver_init()
{
	GPIO_INITIALIZATION();  // Initialize GPIO for the pressure sensor
}



STATE_define(PressureSensorDriver_reading)
{
	PressureSensorDriver_id = PressureSensorDriver_reading; 	 // Set the current state ID
	PressureSensorDriver_pVal = getPressureVal();  				 // Read the pressure sensor value
	set_pressure_val(PressureSensorDriver_pVal); 	 			 // Pass the value to the state management system
	Delay(10000);  												 // Delay for a specified time
}
