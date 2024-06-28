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
	char x;
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c",&x);
	if((x>='A'&& x<='Z') ||(x>='a'&& x<='z'))
	{
		printf("%c is an alphabet",x);

	}
	else
	{
		printf("%c is not an alphabet",x);
	}
	return 0;
}
