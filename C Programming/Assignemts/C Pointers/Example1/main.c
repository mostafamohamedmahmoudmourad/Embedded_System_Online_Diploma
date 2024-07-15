/*
 * main.c
 *
 *  Created on: 15 Jul 2024
 *  Author: Mostafa Mourad
 *
 *  Ex1: Write a program in C to demonstrate how to handle the pointers in the program.
 */

#include <stdio.h>

int main()
{
	int m;												// Declare the integer variable m.
	int* ab;											// Declare the integer pointer ab.
	m=29;												// Assign the value 29 to m.
	printf("Address of m : %p\n",&m);					// Print the address of m.
	printf("Value of m : %d\n",m);						// Print the value of m.
	ab=&m;												// Assign the address of m to the pointer ab.
	printf("\nNow ab is assigned with the address of m.\n");
	printf("Address of pointer ab : %p\n",ab);			// Print the address stored in the pointer ab.
	printf("Content of pointer ab : %d\n",*ab);			// Print the value pointed by ab.
	m=34;												// Assign the value 34 to m.
	printf("\nThe value of m assigned to 34 now.\n");
	printf("Address of pointer ab : %p\n",ab);			// Print the address stored in the pointer ab.
	printf("Content of pointer ab : %d\n",*ab);			// Print the value pointed by ab.
	*ab=7;												// Assign the value 7 to the location pointed by ab.
	printf("\nThe pointer variable ab is assigned with the value 7 now.\n");
	printf("Address of m : %p\n",&m);					// Print the address of m.
	printf("Value of m : %d\n",m);						// Print the value of m.
	return 0;
}
