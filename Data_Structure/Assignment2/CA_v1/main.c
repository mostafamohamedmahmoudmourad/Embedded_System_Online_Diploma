/*
 * main.c
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */

#include "CA.h"

void setup()
{
	// set states pointers
	CA_state = STATE(CA_waiting);
}


void main()
{
	volatile int i;

	setup();

	while(1)
	{
		CA_state();
		for(int i=0; i<1000;i++);
	}
}
