/*
 * main.c
 *
 *  Created on: 4 Aug 2024
 *      Author: Mostafa Mourad
 */

#include "school.h"

void main ()
{
	setbuf(stdout,NULL);
	char temp_text[40];
	while(1)
	{
		printf("\n ========================");
		printf("\n\t Choose on of the following Options \n");
		printf("\n 1: AddStudent ");
		printf("\n 2: Delete_Student ");
		printf("\n 3: View_Student ");
		printf("\n 4: DeleteAll ");
		printf("\n 5: print Student using index");
		printf("\n 6: print length of student database");
		printf("\n 7: print student with reverse index");
		printf("\n Enter Option Number: ");

		gets(temp_text);
		printf("\n=========================");
		switch(atoi(temp_text))
		{
		case 1:
			AddStudent();
			break;
		case 2:
			delete_student();
			break;
		case 3:
			viwe_students();
			break;
		case 4:
			DeleteAll();
			break;
		case 5:
			printStudent();
			break;
		case 6:
			nodesnumber();
			break;
		case 7:
			printStudentRev();
			break;

		default:
			printf("\n Wrong option ");
			break;
		}
	}
}

