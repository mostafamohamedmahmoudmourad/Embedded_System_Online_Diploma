/*
 * main.c
 *
 *  Created on: 12 Jul 2024
 *  Author: Mostafa Mourad
 *
 *	Ex4:C Program to Store Information of Student Using Structure.
 */


#include <stdio.h>

/*--------------------------Data Type Declarations------------------------*/
// Structure Data Type to store the student Information
struct SstudentInformation
{
	char name[40];											// Declaring Array to Store Students Name
	int roll;												// Declaring Variable to Store the Roll Number
	float marks;											// Declaring Variable to Store the Students Marks
}StudInfo[10];


int main()
{
	setbuf(stdout,NULL);
	printf("Enter Information of Students: \n");			//ask user to Enter the Information of Students.
	//for Loop to Take Information of Students.
	for (int i=0;i<2;++i)
	{
		StudInfo[i].roll=i+1;
		printf("\nFor Roll Number%d\n",StudInfo[i].roll);	//to Write The Roll Number.
		printf("Enter Name: ");								//ask User to Enter Name.
		scanf("%s",&StudInfo[i].name);						//Read The Name.
		printf("Enter Marks:");								//ask User to Enter Marks.
		scanf("%f",&StudInfo[i].marks);						//Read The Marks.
		printf("\n");
	}

	printf("Displaying Information of Students:\n\n");
	//for Loop to Print Information of Students.
	for (int i=0;i<2;++i)
	{
		printf("\nInformation of Roll Number %d:\n",i+1);
		printf("Name: ",StudInfo[i].name);
		printf("Marks:%0.2f",StudInfo[i].marks);
	}

	return 0;
}

