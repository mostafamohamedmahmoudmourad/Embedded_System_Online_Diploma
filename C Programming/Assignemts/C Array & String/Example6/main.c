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
	char CharArr[100],CharSearch;
	int IntNumber=0,IntCounter=0;
	setbuf(stdout,NULL);
	printf("Please Enter a String: ");
	gets(CharArr);
	printf("Enter a Character to Find Frequency: ");
	scanf("%c",&CharSearch);
	while(CharArr[IntNumber]!='\0')
	{
		if(CharArr[IntNumber]==CharSearch)
			IntCounter++;
		IntNumber++;
	}
	printf("Frequency of %c is %d\n",CharSearch,IntCounter);

	return 0;
}
