/*
 * main.c
 *
 *  Created on: 12 Jul 2024
 *  Author: Mostafa Mourad
 *
 *  Ex2:  C Programing to add two Distance(in inch - feet) system Using structures.
 */

#include <stdio.h>

struct Distance {
	int feet;
	float inch;

}Distance_t[2],Result;

int main()
{
	setbuf(stdout,NULL);
	/*------------------------------1st-----------------------------------*/
	printf("Enter Information for 1st Distance: \n");           // Read 1st distance from the user
	printf("Enter feet:");										//ask user to enter the first feet number
	scanf("%u",&Distance_t[0].feet);
	printf("Enter inch: ");										//ask user to enter the first inch number
	scanf("%f",&Distance_t[0].inch);
	/*------------------------------2st-----------------------------------*/
	printf("\nEnter Information for 2st Distance: \n");         // Read 2st distance from the user
	printf("Enter feet:");										//ask user to enter the second feet number
	scanf("%d",&Distance_t[1].feet);
	printf("Enter inch: ");										//ask user to enter the second inch number
	scanf("%f",&Distance_t[1].inch);
	/*-------------------------------------------------------------------*/
	Result.feet=Distance_t[0].feet+Distance_t[1].feet;          //add distances in feet
	Result.inch=Distance_t[0].inch+Distance_t[1].inch;			//add distances in inch
	if(Result.inch>=12){										//check if inch number more than feet
		Result.inch-=12;
		++Result.feet;
	}
	printf("Sum of Distance %d %.2f",Result.feet,Result.inch);	// print the sum of all distances
	return 0;
}