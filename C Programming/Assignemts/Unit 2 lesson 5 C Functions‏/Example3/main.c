/*
 * main.c
 *
 *  Created on: 5 Jul 2024
 *      Author: Mostafa Mourad
 */


#include <stdio.h>
#include <stdlib.h>

void Reverse();

int main()
{
	setbuf(stdout,NULL);
	printf("Enter a Sentence: ");
	Reverse();
	return 0;
}


void Reverse()
{
	char c;
	scanf("%c",&c);
	if(c!='\n')
	{
		Reverse();
		printf("%c",c);
	}
}
