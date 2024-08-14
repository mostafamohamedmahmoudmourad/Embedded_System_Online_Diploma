/*
 * DC.c
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */



#include "DC.h"

int DC_speed=0;

//state pointer to function.
void (*DC_state)();


void DC_init()
{
	printf("DC init \n");
}


void DC_motor(int s)
{
	DC_speed =  s;
	STATE(DC_busy);
	printf("CA---------Speed = %d -------DC \n",DC_speed);
}


STATE_define(DC_idle)
{
	//state_Name
	DC_state_id = DC_idle;


	printf("DC_idle State: speed=%d  distance=%d \n",DC_speed);

}

STATE_define(DC_busy)
{
	//state_Name
	DC_state_id = DC_busy;

	DC_state = STATE(DC_busy);

	printf("DC_busy State: speed=%d \n",DC_speed);
}
