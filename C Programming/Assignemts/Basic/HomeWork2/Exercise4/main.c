/*
 * main.c
 *
 *  Created on: 27 Jun 2024
 *      Author: Mostafa Mourad
 */


#include <stdio.h>
#include <stdlib.h>

int main()
{
	float num;
	printf("Enter a number: ");
	fflush(stdout);
	scanf("%f",&num);
	if(num>0)
	{
		printf("%.2f is positive",num);

	}
	else if(num<0.0000)
	{
		printf("%.2f is negative",num);
	}
	else
	{
		printf("your number = zero > %.2f",num);
	}
	return 0;
}
