/*
 * PressureSensorDriver.h
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef PRESSURESENSORDRIVER_H_  // Prevent multiple inclusions of this header
#define PRESSURESENSORDRIVER_H_

#include "state.h"
#include "driver.h"



// Enum to define the state of the pressure sensor driver
enum {
	PressureSensorDriver_reading  // State ID for reading sensor data
} PressureSensorDriver_id;


// Declare the state function for reading sensor data
STATE_define(PressureSensorDriver_reading);


// Function prototype to initialize the pressure sensor driver
void PressureSensorDriver_init();

// Pointer to the current state function of the pressure sensor driver
extern void (* PressureSensorDriver_state)();

#endif /* PRESSURESENSORDRIVER_H_ */
