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
	int  IntNumber=0 ,IntCounter=0 ,IntIns=0, IntLocation=0 ,counter=0;
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
	printf("Enter The Number You Want to inserted: ");
	scanf("%d",&IntIns);
	printf("Enter The Location: ");
	scanf("%d",&IntLocation);
	IntLocation--;
	for(counter=IntNumber;counter>=IntLocation;counter--)
	{
		IntArr[counter]=IntArr[counter-1];
	}
	IntNumber++;
	IntArr[IntLocation]=IntIns;
	for(counter=0;counter<IntNumber;counter++)
	{
		printf("%d ",IntArr[counter]);
	}
	return 0;
}