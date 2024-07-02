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
	char CharArr[100];
	int IntNumber=0,IntStrlen=0;
	setbuf(stdout,NULL);
	printf("Please Enter a String: ");
	gets(CharArr);
	while(CharArr[IntNumber]!='\0')
	{
		IntNumber++;
	}
	IntStrlen=IntNumber;
	printf("Reverse String is: ");
	for(IntNumber=IntStrlen-1;IntNumber>=0;IntNumber--)
	{
		printf("%c",CharArr[IntNumber]);
	}


	return 0;
}

