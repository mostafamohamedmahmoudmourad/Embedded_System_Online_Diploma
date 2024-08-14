/*
 * US.c
 *
 *  Created on: 7 Aug 2024
 *      Author: Mostafa Mourad
 */


#include "US.h"

int US_distance =0;


//state pointer to function.
void (*US_state)();
int Get_distance_random(int l,int r, int count);

void US_init()
{
	printf("US init\n");
}


STATE_define(US_busy)
{
	//state_Name
	US_state_id = US_busy;

	//state_Action
	US_distance = Get_distance_random(45,55,1);
	printf("CA_waiting State:  distance=%d \n",US_distance);
	US_set_distance(US_distance);
	US_state = STATE(US_busy);

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


