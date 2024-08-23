/*
 * MainAlg.c
 *
 *  Created on: 12 Aug 2024
 *      Author: Mostafa Mourad
 */

#include "MainAlg.h"

static int MainAlg_Pval = 0;  // Variable to store the pressure value in the main algorithm
static int MainAlg_threshold = 20;  // Threshold value for detecting high pressure



void (* MainAlg_state)();  // Function pointer to the current state function

// Function to set the pressure value
void set_pressure_val(int Pval)
{
	MainAlg_Pval = Pval;  // Update the pressure value
}



// State function for high-pressure detection
STATE_define(MainAlg_high_pressure_delection)
{
	MainAlg_state_id = MainAlg_high_pressure_delection;  // Set the current state ID

	// Check if the pressure value exceeds the threshold
	if (MainAlg_Pval > MainAlg_threshold)
		HighPressure_detected();  // Trigger high-pressure detection action
}
