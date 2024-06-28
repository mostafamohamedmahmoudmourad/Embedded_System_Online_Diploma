/*
 * main.c
 *
 *  Created on: 27 Jun 2024
 *      Author: Mostafa Mourad
 */
/*
	EX7:
	it is an interview trick

	Write Source Code to Swap Two Numbers without temp variable.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	float num1,num2;
	printf("Enter value of num1: ");
	fflush(stdout);
	scanf("%f",&num1);
	printf("Enter value of num2: ");
	fflush(stdout);
	scanf("%f",&num2);
	num1+=num2;
	num2=num1-num2;
	num1-=num2;
	printf("\n");
	printf("After swapping, value of num1: %0.2f\n",num1);
	printf("After swapping, value of num2: %0.2f",num2);
	return 0;
}
