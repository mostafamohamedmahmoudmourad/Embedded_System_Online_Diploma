/*
 * main.c
 *
 *  Created on: 12 Jul 2024
 *      Author: Mostafa Mourad
 *
 */


#include <stdio.h>

/*--------------------------Data Type Declarations------------------------*/

union UJob
{
	char name[32];
	float salary;
	int worker_no;
}UUnion;

struct SJob
{
	char name[32];
	float salary;
	int worker_no;
}SStruct;

int main()
{
	printf("Size of The Union= %d\n",sizeof(UUnion));					//Print The Size of Union.
	printf("Size of The Structure= %d",sizeof(SStruct));				//Print The Size of Structure.
	return 0;
}
