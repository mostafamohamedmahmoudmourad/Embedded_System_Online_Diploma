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
	float num1 ,num2 ;
	char operator;
	printf("Enter operator either + or - or * : ");
	fflush(stdout);
	scanf("%c",&operator);

	printf("Enter two numbers: ");
	fflush(stdout);
	scanf("%f %f",&num1,&num2);
	switch(operator)
	{
		case'+':
			printf("%0.2f + %0.2f = %0.2f",num1,num2,num1+num2);
			break;
		case'-':
			printf("%0.2f - %0.2f = %0.2f",num1,num2,num1-num2);
			break;
		case'*':
			printf("%0.2f * %0.2f = %0.2f",num1,num2,num1*num2);
			break;
		default:
			printf("Error!!!");
			break;
	}
	return 0;
}


