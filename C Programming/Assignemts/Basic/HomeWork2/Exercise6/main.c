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
	int num , count ,Sum=0 ;
	printf("Enter your number: ");
	fflush(stdout);
	scanf("%d",&num);
	for(count=0;count<=num;count++)
	{
		Sum+=count;
	}
	printf("Sum = %d",Sum);
	return 0;
}
