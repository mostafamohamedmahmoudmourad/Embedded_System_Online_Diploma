/*
 * main.c
 *
 *  Created on: 15 Jul 2024
 *      Author: Mostafa Mourad
 *
 *  Ex3: Write a program in C to print a string in reverse using a pointer
 */


#include <stdio.h>

int main()
{
    // Declare an array to store the input string
    char str[50];
    // Declare another array to store the reversed string
    char revstr[50];
    // Declare a pointer to the input string
    char *stptr = str;
    // Declare a pointer to the reversed string
    char *revptr = revstr;
    // Initialize a counter
    int i=-1;

    // Clear the output buffer
    setbuf(stdout,NULL);

    // Print the task to the console
    printf("Pointer : Print a string in reverse order : \n\n");
    printf("------------------------------------------------\n\n");

    // Ask the user for input
    printf("Input a string : ");
    scanf("%s",str);

    // Traverse the input string to the end
    while(*stptr)
    {
        stptr++;
        i++;
    }

    // Traverse the string in reverse order and copy each character to the reversed string
    for(;i>=0;--i)
    {
        stptr--;
        *revptr = *stptr;
        revptr++;
    }

    // Add the null character at the end of the reversed string
    *revptr='\0';

    // Print the reversed string
    printf("Reverse of the string is : %s \n\n",revstr);

    return 0;
}


