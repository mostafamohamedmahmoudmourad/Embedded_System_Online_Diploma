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
	int num , count ;
	long long int   mult=1;
	printf("Enter your number: ");
	fflush(stdout);
	scanf("%d",&num);
	if(num<0000)
	{
		printf("Error! Factorial of negative number does't exist");
	}
	else
	{
		for(count=1;count<=num;++count)
		{
			mult*=count;
		}
		printf("Factorial = %lu",mult);
	}
	return 0;
}
