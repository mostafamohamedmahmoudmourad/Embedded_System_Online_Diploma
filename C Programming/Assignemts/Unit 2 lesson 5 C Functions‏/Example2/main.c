/*
 * main.c
 *
 *  Created on: 4 Jul 2024
 *      Author: Mostafa Mourad
 */

#include <stdio.h>
#include <stdlib.h>


int factorial(int IntNumber);    // function declaration

int main()
{
	int number=0;
	setbuf(stdout,NULL);
	printf("Enter an Positive Number: ");
	scanf("%d",&number);
	printf("Factorial of %d = %d",number,factorial(number));


	return 0;
}

int factorial(int IntNumber)
{
	if(IntNumber==0 || IntNumber==1)
		return 1;
	else
		return (IntNumber*factorial(IntNumber-1));
}


