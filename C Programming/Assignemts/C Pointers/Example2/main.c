/*
 * main.c
 *
 *  Created on: 15 Jul 2024
 *      Author: Mostafa Mourad
 *
 *  Ex2: Write a program in C to print all the alphabets using a pointer. Go to the editor
 */

#include <stdio.h>

int main()
{
	char alph[27];				// Declaring Array to Store Alphabets.
	int x;						// Declaring The Variable to used in loop.
	char* ptr;					//declaration The Pointer & ptr is a Pointer of character.

	ptr = alph;
	//Loop to Store All The Alphabets.
	for(x=0;x<26;x++)
	{
		*ptr=x+'A';
		++ptr;
	}
	ptr = alph;
	//Loop to print All The Alphabets.
	printf("The Alphabets are : \n");
	for (x=0;x<26;x++)
	{
		printf("%c  ",*ptr);
		ptr++;
	}
	return 0;
}
