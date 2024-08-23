/*
 * MainAlg.h
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef MAINALG_H_  // Prevent multiple inclusions of this header
#define MAINALG_H_

#include "state.h"
#include "driver.h"



// Enum to define the states for the Main Algorithm
enum
{
	MainAlg_high_pressure_delection  // State ID for high-pressure detection
} MainAlg_state_id;


// Declare the state function for high-pressure detection
STATE_define(MainAlg_high_pressure_delection);

// Pointer to the current state function of the Main Algorithm
extern void (* MainAlg_state)();

#endif /* MAINALG_H_ */
