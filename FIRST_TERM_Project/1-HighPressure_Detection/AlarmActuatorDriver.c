/*
 * AlarmActuatorDriver.c
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#include "AlarmActuatorDriver.h"

#define Alarm_off 0  // Define the value for the alarm off state
#define Alarm_on  1  // Define the value for the alarm on state

void (* AlarmActuatorDriver_state)();  // Function pointer to the current state function





// Function to initialize the alarm actuator driver
void AlarmActuatorDriver_init()
{
	GPIO_INITIALIZATION();  // Initialize GPIO for the alarm actuator
}


// Function to start the alarm
void StartAlarm()
{
	AlarmActuatorDriver_state = STATE(AlarmActuatorDriver_AlarmOn);  // Switch to the alarm on state
	AlarmActuatorDriver_state();  // Execute the current state function
}



// Function to stop the alarm
void StopAlarm()
{
	AlarmActuatorDriver_state = STATE(AlarmActuatorDriver_AlarmOff);  // Switch to the alarm off state
	AlarmActuatorDriver_state();  // Execute the current state function
}




// State function for waiting (idle) state
STATE_define(AlarmActuatorDriver_waiting)
{
	AlarmActuatorDriver_state_id = AlarmActuatorDriver_waiting;  // Set the current state ID
}




// State function for when the alarm is on
STATE_define(AlarmActuatorDriver_AlarmOn)
{
	AlarmActuatorDriver_state_id = AlarmActuatorDriver_AlarmOn;  // Set the current state ID


	Set_Alarm_actuator(0);  // Activate the alarm actuator

	AlarmActuatorDriver_state = STATE(AlarmActuatorDriver_waiting);  // Switch to the waiting state
}




// State function for when the alarm is off
STATE_define(AlarmActuatorDriver_AlarmOff)
{
	AlarmActuatorDriver_state_id = AlarmActuatorDriver_AlarmOff;  // Set the current state ID

	Set_Alarm_actuator(1);  // Deactivate the alarm actuator

	AlarmActuatorDriver_state = STATE(AlarmActuatorDriver_waiting);  // Switch to the waiting state
}
