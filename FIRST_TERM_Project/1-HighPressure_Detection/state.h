/*
 * state.h
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef STATE_H_  // Prevent multiple inclusions of this header
#define STATE_H_

// Macro to define a state function
#define STATE_define(_statFUN_) 	void ST_##_statFUN_()

// Macro to call a state function
#define STATE(_statFUN_) 			ST_##_statFUN_

// Function prototypes for handling pressure and alarms
void set_pressure_val(int Pval);
void HighPressure_detected();
void StartAlarm();
void StopAlarm();

#endif /* STATE_H_ */
