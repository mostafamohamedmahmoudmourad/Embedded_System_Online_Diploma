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
int Get_distance_random(int l,int r, int count);


STATE_define(CA_waiting)
{
	//state_Name
	CA_state_id = CA_waiting;
	//state_Action
	CA_speed = 0;
	//Event_Check
	CA_distance = Get_distance_random(45,55,1);
	(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	printf("CA_waiting State: speed=%d  distance=%d \n",CA_speed,CA_distance);
}

STATE_define(CA_driving)
{
	//state_Name
		CA_state_id = CA_driving;
		//state_Action
		CA_speed = 30;
		//Event_Check
		CA_distance = Get_distance_random(45,55,1);
		(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
		printf("CA_waiting State: speed=%d  distance=%d \n",CA_speed,CA_distance);
}


int Get_distance_random(int l,int r, int count)
{
	int i, rand_num;
	for(i=0;i<count;i++)
	{
		rand_num = ( rand() % (r - l + 1))+l;
		return rand_num;
	}

}