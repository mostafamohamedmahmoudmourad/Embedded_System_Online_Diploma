/*
 * main.c
 *
 *  Created on: 12 Jul 2024
 *  Author: Mostafa Mourad
 *
 *  Ex3: C Program to Add Two Complex Number by Passing Structure to a Fanction.
 */


#include <stdio.h>
/*--------------------------Data Type Declarations------------------------*/
// Structure Data Type to Store the Complex Number
typedef struct SComplex{
	float realNumber;										// declaration the Real of the Complex Number
	float imagNumber;										// declaration the Imaginary of the Complex Number
}Complex;

/*--------------------------Function declarations------------------------*/

// Function that adds the real and imaginary part of both complex numbers
Complex AddComplex(Complex NumberOne,Complex NumberTwo);

int main()
{
	setbuf(stdout,NULL);

	Complex NumberOne,NumberTwo,Result;
	printf("For 1st Complex Number:\n");

	//ask the user to Enter 1st  Real and Imaginary Part of Complex Number
	printf("Enter Real and Imaginary Part of Complex Number Respectively: \n");
	scanf("%f %f",&NumberOne.realNumber,&NumberOne.imagNumber);

	//ask the user to Enter 2st  Real and Imaginary Part of Complex Number
	printf("Enter Real and Imaginary Part of Complex Number Respectively: \n");
	scanf("%f %f",&NumberTwo.realNumber,&NumberTwo.imagNumber);

	//Using the AddComplex function to add the real and imaginary parts of both complex numbers.
	Result=AddComplex(NumberOne,NumberTwo);

	printf("The Result= %.2f+%.2fi",Result.realNumber,Result.imagNumber);
	return 0;
}


/*--------------------------Function definitions------------------------*/
Complex AddComplex(Complex NumberOne,Complex NumberTwo)
{
	Complex Result;
	// Adding the real and imaginary parts together
	Result.realNumber=NumberOne.realNumber+NumberTwo.realNumber;
	Result.imagNumber=NumberOne.imagNumber+NumberTwo.imagNumber;

	return Result;    //Return the result of the addition for the numbers
}

