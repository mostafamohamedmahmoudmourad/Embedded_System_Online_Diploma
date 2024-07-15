/*
 * main.c
 *
 *  Created on: 15 Jul 2024
 *      Author: Mostafa Mourad
 *
 *  Ex4: Write a program in C to print the elements of an array in reverse order.
 */

#include <stdio.h>

int main()
{
	// Declare variables
	int n, counter, arr[20];
	int *ptr;

	// Disable buffer for stdout
	setbuf(stdout, NULL);

	// Ask user for number of elements to store in the array
	printf("Input the number of elements to store in the array (max 15) : ");
	scanf("%d", &n);

	// Point ptr to the first element of the array
	ptr = &arr[0];

	// Loop to get elements from user
	for(counter = 0; counter < n; counter++)
	{
		printf("Element --> %d : ", counter + 1);
		scanf("%d", ptr);
		ptr++;
	}

	// Point ptr to the last element of the array
	ptr = &arr[n - 1];

	// Print the elements of array in reverse order
	printf("The elements of array in reverse order are :\n");
	for (counter = n; counter > 0; counter--)
	{
		printf("\nElement --> %d : %d \n", counter, *ptr);
		ptr--;
	}

	return 0;
}

