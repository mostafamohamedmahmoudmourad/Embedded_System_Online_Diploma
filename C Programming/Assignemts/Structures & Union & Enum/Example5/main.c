/*
 * main.c
 *
 *  Created on: 12 Jul 2024
 *  Author: Mostafa Mourad
 *
 *  Ex5: C Program to Find Area of a Circle,Passing Arguments to Macros.
 */


#include <stdio.h>

/*-----------------------MACRO Declarations--------------------*/
#define PI 3.14
/*--------------------------Function declarations------------------------*/
//Function to Calculates The Circle of Area.
double AreaOfCircle(float radius);

int main()
{
	setbuf(stdout,NULL);
	float radius;											//Declare The Variable For The Radius.
	printf("Enter The Radius of The Circle: ");				//Ask User to Enter The Radius of The Circle .
	scanf("%f",&radius);									//Store The Radius of Circle.

	printf("The Area of The Circle= %.2f",AreaOfCircle(radius));		//Print The Area of Circle.
	return 0;
}

/*--------------------------Function definitions------------------------*/

double AreaOfCircle(float radius)
{
	float area=0;											//Declare The Variable to calc the Radius.
	area=(PI*radius*radius);								//Area=(PI*r^2)
	return area;
}
