/*
 * AlarmMonitor.c
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#include "AlarmMonitor.h"

static int AlarmMonitor_periode = 60000;  // Duration for which the alarm stays on
void (* AlarmMonitor_state)();  // Function pointer to the current state function

// Function to handle high-pressure detection
void HighPressure_detected()
{
	AlarmMonitor_state = STATE(AlarmMonitor_alarmOn);  // Switch to the alarm on state
}

// State function for when the alarm is off
STATE_define(AlarmMonitor_alarmOff)
{
	AlarmMonitor_state_id = AlarmMonitor_alarmOff;  // Set the current state ID
	StopAlarm();  // Stop the alarm
}

// State function for when the alarm is on
STATE_define(AlarmMonitor_alarmOn)
{
	AlarmMonitor_state_id = AlarmMonitor_alarmOn;  // Set the current state ID

	StartAlarm();  // Start the alarm
	Delay(AlarmMonitor_periode);  // Keep the alarm on for a specified duration
	StopAlarm();  // Stop the alarm
	AlarmMonitor_state = STATE(AlarmMonitor_alarmOff);  // Switch to the alarm off state
}












