/*
 * main.c
 *
 *  Created on: 4 Jul 2024
 *  Author: Mostafa Mourad
 *
 */

#include <stdio.h>
#include <stdlib.h>

int CheckPrimeNumber(int IntCheckNumber);   // function declaration

int main()
{

	int number1,number2,counter;
	setbuf(stdout,NULL);
	printf("Enter Two Number: ");
	scanf("%d %d",&number1,&number2);
	printf("Prime Number between %d and %d are: ",number1,number2);
	for(counter=number1+1;counter<number2;counter++)
	{
		if(CheckPrimeNumber(counter)==0)
		{
			printf("%d ",counter);
		}
	}
	return 0;
}

int CheckPrimeNumber(int IntCheckNumber)       //function definition
{
	int Intcount=0,flag=0;
	for(Intcount=2;Intcount<IntCheckNumber;Intcount++)
	{
		if(IntCheckNumber%Intcount==0)
		{
			flag=1;
			break;
		}
	}
	return flag;
}
