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
	int  IntNumber=0 ,IntCounter=0 ,IntSearch=0, counter=0, IntIndex=0;
	int IntArr[10];
	setbuf(stdout,NULL);
	printf("Enter The Number of Element ");
	scanf("%d",&IntNumber);
	for(IntCounter=0;IntCounter<IntNumber;IntCounter++)
	{
		scanf("%d",&IntArr[IntCounter]);
	}
	for(IntCounter=0;IntCounter<IntNumber;IntCounter++)
	{
		printf("%d\n",IntArr[IntCounter]);
	}
	printf("Enter The Number You Want to Search in Array: ");
	scanf("%d",&IntSearch);
	for(counter=0;counter<IntNumber;counter++)
	{
		if(IntArr[counter]==IntSearch)
			break;
		IntIndex++;
	}
	printf("The Number %d Found at index %d",IntSearch,IntIndex+1);
	return 0;
}