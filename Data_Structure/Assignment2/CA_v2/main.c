/*
 * main.c
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */

#include "CA.h"
#include "US.h"
#include "DC.h""

void setup()
{
	// init Block
	DC_init();
	US_init();
	// set states pointers
	CA_state = STATE(CA_waiting);
	US_state =  STATE(US_busy);
	DC_state =  STATE(DC_idle);
}


void main()
{
	volatile int i;

	setup();

	while(1)
	{
		// Call state for each Block
		US_state();
		CA_state();
		DC_state();
		//delay
		for(int i=0; i<1000;i++);
	}
}

