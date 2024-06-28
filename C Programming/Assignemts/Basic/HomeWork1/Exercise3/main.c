/*
 * main.c
 *
 *  Created on: 27 Jun 2024
 *      Author: Mostafa Mourad
 */

/*
	EX3:

	Write C Program to Add Two Integers
	i should see the Console as following:
	##########Console-output###
	Enter two integers: 12
	11
	Sum: 23
	###########################
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num1,num2,Sum;
	printf("Please Enter two integers: ");
	fflush(stdout);
	scanf("%i%i",&num1,&num2);
	Sum=num1+num2;
	printf("Sum: %d",Sum);
	return 0;
}
