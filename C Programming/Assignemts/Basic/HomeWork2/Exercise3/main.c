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
	float num1,num2,num3;
	printf("Enter three numbers: ");
	fflush(stdout);
	scanf("%f %f %f",&num1,&num2,&num3);
	if(num1>num2)
	{
		if(num1>num3)
		{
			printf("largest number = %.2f",num1);
		}
		else
		{
			printf("largest number = %.2f",num3);
		}
	}
	else if(num2>num3)
	{
		printf("largest number = %.2f",num2);
	}
	else
	{
		printf("largest number = %.2f",num3);
	}
	return 0;
}
