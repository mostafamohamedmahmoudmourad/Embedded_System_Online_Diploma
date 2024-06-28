/*
 * main.c
 *
 *  Created on: 27 Jun 2024
 *      Author: Mostafa Mourad
 */

/*
	EX4:

	Write C Program to Multiply two Floating Point Numbers
	i should see the Console as following:
	##########Console-output###
	###########################
	Enter two numbers: 2.4
	1.1
	Product: 2.640000
	########################################################################
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	float num1,num2,Mult;
	printf("Please Enter two numbers: ");
	fflush(stdout);
	scanf("%f%f",&num1,&num2);
	Mult=num1*num2;
	printf("Product: %f",Mult);
	return 0;
}
