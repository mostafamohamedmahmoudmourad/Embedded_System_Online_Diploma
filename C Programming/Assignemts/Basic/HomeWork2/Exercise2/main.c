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
	printf("Enter an alphabet: ");
	fflush(stdout);
	scanf("%c",&x);
	if(x=='A'||x=='a'||x=='E'||x=='e'||x=='I'||x=='i'||x=='O'||x=='o'||x=='U'||x=='u')
	{
		printf("%c is vowel\n",x);
	}
	else
	{
		printf("%c is consonant",x);
	}
	return 0;
}


