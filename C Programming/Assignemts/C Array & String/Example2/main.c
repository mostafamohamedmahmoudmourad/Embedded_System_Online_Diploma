/*
 * main.c
 *
 *  Created on: 30 Jun 2024
 *      Author: Mostafa Mourad
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	float arr[50],average=0.0;
	int counter,int_number ;
	int sum=0;
	setbuf(stdout,NULL);
	printf("Enter the number of date <(50) : ");
	scanf("%d",&int_number);
	if(int_number>50||int_number<0) //check number
	{
		printf("Error!! Please Enter your number again");

	}
	else
	{
		for(counter=0;counter<int_number;counter++)
		{
			printf("Enter A Number ");
			scanf("%f",&arr[counter]);
		}
		for(counter=0;counter<int_number;counter++)
		{
			sum+=arr[counter];
		}
		average=sum/int_number; // to get the average number
		printf("Average of Element is %f",average);
	}
	return 0;
}




