/*
 * school.h
 *
 *  Created on: 4 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef SCHOOL_H_
#define SCHOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stddef.h>

#define DPRINTF(...)	{fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__); \
		fflush(stdout); \
		fflush(stdin);}


struct Sdata {
	int ID ;
	char name[40];
	float leight;
};

struct SStudent
{
	struct Sdata student;
	struct SStudent* PNextStudent;
};


void AddStudent();
int  delete_student();
void viwe_students();
void DeleteAll();
void printStudent();
void nodesnumber();
void printStudentRev();



#endif /* SCHOOL_H_ */
