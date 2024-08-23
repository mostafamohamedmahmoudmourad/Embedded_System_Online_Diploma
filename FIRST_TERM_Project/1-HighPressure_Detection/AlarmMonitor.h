/*
 * AlarmMonitor.h
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef ALARMMONITOR_H_  // Prevent multiple inclusions of this header
#define ALARMMONITOR_H_

#include "state.h"
#include "driver.h"



// Enum to define the states for the alarm monitor
enum {
	AlarmMonitor_alarmOff,  // State ID for when the alarm is off
	AlarmMonitor_alarmOn    // State ID for when the alarm is on
} AlarmMonitor_state_id;


// Declare state functions for alarm on and off states
STATE_define(AlarmMonitor_alarmOff);
STATE_define(AlarmMonitor_alarmOn);

// Pointer to the current state function of the alarm monitor
extern void (* AlarmMonitor_state)();

#endif /* ALARMMONITOR_H_ */
