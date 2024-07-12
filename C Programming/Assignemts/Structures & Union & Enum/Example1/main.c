/*
 * main.c
 *
 *  Created on: 11 Jul 2024
 *  Author: Mostafa Mourad
 *
 *  Ex1
 */

#include <stdio.h>

struct student{
	char name[50];
	int roll;
	float marks;

}student_t;

int main()
{
	setbuf(stdout,NULL);
	printf("Enter Information of Students: \n\n");
	printf("Enter Name: ");
	scanf("%s",&student_t.name);
	printf("Enter Roll Number: ");
	scanf("%d",&student_t.roll);
	printf("Enter Marks: ");
	scanf("%f",&student_t.marks);
	printf("\n");
	printf("Displaying Information\n");
	printf("Name: %s\n",student_t.name);
	printf("Roll: %d\n",student_t.roll);
	printf("Marks: %.2f\n",student_t.marks);
	return 0;
}

