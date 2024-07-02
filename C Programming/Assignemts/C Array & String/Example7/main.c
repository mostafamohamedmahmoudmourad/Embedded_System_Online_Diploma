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
	int IntNumber=0,Intstrlen=0;
	setbuf(stdout,NULL);
	printf("Please Enter a String: ");
	gets(CharArr);
	while(CharArr[IntNumber]!='\0')
	{
		IntNumber++;
	}
	Intstrlen=IntNumber;
	printf("The Length of String = %d\n",Intstrlen);


	return 0;
}
