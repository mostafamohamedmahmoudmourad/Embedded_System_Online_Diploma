/*
 * CA.c
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */


#include "CA.h"

int CA_speed=0;
int CA_distance =0;
int CA_threshold =50;


//state pointer to function.
void (*CA_state)();

void US_set_distance(int d)
{
	CA_distance =  d;
	(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	printf("US---------distance = %d -------CA \n",CA_distance);
}



STATE_define(CA_waiting)
{
	//state_Name
	CA_state_id = CA_waiting;
	printf("CA_waiting State: speed=%d  distance=%d \n",CA_speed,CA_distance);
	//state_Action
	CA_speed = 0;
	DC_motor(CA_speed);

}

STATE_define(CA_driving)
{
	//state_Name
		CA_state_id = CA_driving;
		printf("CA_waiting State: speed=%d  distance=%d \n",CA_speed,CA_distance);
		//state_Action
		CA_speed = 30;
		DC_motor(CA_speed);

}
