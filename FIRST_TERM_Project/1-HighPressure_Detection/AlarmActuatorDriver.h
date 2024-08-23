/*
 * AlarmActuatorDriver.h
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef ALARMACTUATORDRIVER_H_  // Prevent multiple inclusions of this header
#define ALARMACTUATORDRIVER_H_

#include "state.h"
#include "driver.h"

// Enum to define the states for the alarm actuator driver
enum {
	AlarmActuatorDriver_waiting,  // State ID for waiting state
	AlarmActuatorDriver_AlarmOn,  // State ID for when the alarm is on
	AlarmActuatorDriver_AlarmOff  // State ID for when the alarm is off
} AlarmActuatorDriver_state_id;


// Declare state functions for the alarm actuator driver
STATE_define(AlarmActuatorDriver_waiting);
STATE_define(AlarmActuatorDriver_AlarmOn);
STATE_define(AlarmActuatorDriver_AlarmOff);


// Function to initialize the alarm actuator driver
void AlarmActuatorDriver_init();

// Pointer to the current state function of the alarm actuator driver
extern void (* AlarmActuatorDriver_state)();

#endif /* ALARMACTUATORDRIVER_H_ */
