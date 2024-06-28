/*
 * main.c
 *
 *  Created on: 27 Jun 2024
 *      Author: Mostafa Mourad
 *
 */

/*
	EX6:

	Write Source Code to Swap Two Numbers
	#########Console_output######
	Enter value of a: 1.20
	Enter value of b: 2.45

	After swapping, value of a = 2.45
	After swapping, value of b = 1.2
	#############################
	########################################################################
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	float num1,num2,num3;
	printf("Enter value of num1: ");
	fflush(stdout);
	scanf("%f",&num1);
	printf("Enter value of num2: ");
	fflush(stdout);
	scanf("%f",&num2);
	num3=num1;
	num1=num2;
	num2=num3;
	printf("After swapping, value of num1: %0.2f\n",num1);
	printf("After swapping, value of num2: %0.2f",num2);
	return 0;
}
