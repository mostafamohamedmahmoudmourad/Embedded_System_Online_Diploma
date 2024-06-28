/*
 * main.c
 *
 *  Created on: 27 Jun 2024
 *      Author: Mostafa Mourad
 */

/*
	EX2:

	Write C Program to Print a Integer Entered by a User
	i should see the Console as following:
	##########Console-output###
	Enter a integer: 25
	You entered: 25
	###########################
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int number=0;
    printf("Enter a integer: ");
    fflush(stdout);
    scanf("%i",&number);
    printf("You entered: %i",number);
    return 0;
}
