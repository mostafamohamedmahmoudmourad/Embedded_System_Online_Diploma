/*
 * main.c
 *
 *  Created on: 27 Jun 2024
 *      Author: Mostafa Mourad
 */

/*
	EX5:

	Write C Program to Find ASCII Value of a Character

	#########Console_output######
	Enter a character: G
	ASCII value of G = 71
	#############################
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a;
	printf("Please Enter a character:");
	fflush(stdout);
	scanf("%c",&a);
	printf("ASCII value of %c = %i",a,a);

	return 0;
}
