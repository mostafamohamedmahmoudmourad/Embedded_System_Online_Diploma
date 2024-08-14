/*
 * school.c
 *
 *  Created on: 4 Aug 2024
 *      Author: Mostafa Mourad
 */


#include "school.h"


struct SStudent* gpFirstStudent = NULL;



void AddStudent()
{
	struct SStudent* pNewStudent;
	struct SStudent* pLastStudent;
	char temp_text[40];
	if(gpFirstStudent==NULL)
	{
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));

		gpFirstStudent = pNewStudent;
	}
	else
	{
		pLastStudent = gpFirstStudent;
		while(pLastStudent->PNextStudent)
			pLastStudent = pLastStudent->PNextStudent;
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		pLastStudent->PNextStudent = pNewStudent;
	}
	//full new record
	printf("\n Enter the ID: ");
	gets(temp_text);
	pNewStudent->student.ID = atoi(temp_text);

	printf("\n Enter student full name: ");
	gets(pNewStudent->student.name);


	printf("\n Enter the height: ");
	gets(temp_text);
	pNewStudent->student.leight = atof(temp_text);
	//set the next pointer null.
	pNewStudent->PNextStudent = NULL;

}

int delete_student()
{
	char temp_text[40];
	unsigned int selected_id;

	printf("\n Enter the student id to be deleted: ");
	gets(temp_text);
	selected_id = atoi(temp_text);

	if(gpFirstStudent)
	{
		struct SStudent* pSelectedStudent = gpFirstStudent;
		struct SStudent* pPreviousStudent = NULL;

		while(pSelectedStudent)
		{
			if(pSelectedStudent->student.ID == selected_id)
			{
				if(pPreviousStudent)
				{
					pPreviousStudent->PNextStudent = pSelectedStudent->PNextStudent;
				}
				else
				{
					gpFirstStudent = pSelectedStudent->PNextStudent;
				}
				free(pSelectedStudent);
				return 1;
			}
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->PNextStudent;
		}
	}
	printf("\n cannot find student ID.");
	return 0;
}









void viwe_students()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	int count = 0;
	if(gpFirstStudent == NULL)
	{
		printf("\n Empty list");
	}
	else
	{
		while(pCurrentStudent)
		{
			printf("\n record number %d", count+1);
			printf("\n \t ID: %d",pCurrentStudent->student.ID);
			printf("\n \t Name: %s",pCurrentStudent->student.name);
			printf("\n \t Height: %f ",pCurrentStudent->student.leight);
			pCurrentStudent = pCurrentStudent->PNextStudent;
			count++;
		}
	}
}







void DeleteAll()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	if(gpFirstStudent == NULL)
	{
		printf("\n Empty list");
	}
	else
	{
		while(pCurrentStudent)
		{
			struct SStudent* pTempStudent = pCurrentStudent;
			pCurrentStudent = pCurrentStudent->PNextStudent;
			free(pTempStudent);
		}
		gpFirstStudent = NULL;
	}
}



void printStudent()
{
	struct SStudent* pIndexStudent= gpFirstStudent;
    char index[5];
    printf("please index number of student: ");
    gets(index);
    int count = 1;
    while(pIndexStudent)
    {
        if(count==atoi(index))
        {
            break;
        }
        pIndexStudent = pIndexStudent->PNextStudent;
        count++;
    }
    if(count == atoi(index)){
		printf("\tstudent ID : %d\n",pIndexStudent->student.ID);
		printf("\tstudent Name : %s\n",pIndexStudent->student.name);
		printf("\tstudent Leight : %f\n",pIndexStudent->student.leight);
		printf("\t-----------------\n");
	}
	else{
		printf("this index not found in database\n");
	}

}


void nodesnumber()
{
	struct SStudent* pnodesnumber   = gpFirstStudent;
    int count = 1;
    while(pnodesnumber->PNextStudent)
    {
        count++;
        pnodesnumber = pnodesnumber->PNextStudent;
    }

    printf("length of student database equal : %d node \n",count);

}

void printStudentRev(){
	char index_rev[5];
	int len=1;
	int count=1;
	int index;
	struct SStudent* pIndexStudent = gpFirstStudent;
	struct SStudent* pStudentRev = gpFirstStudent;
	printf("please rev_index number of student: ");
	gets(index_rev);
	while(pStudentRev->PNextStudent){
		len++;
		pStudentRev = pStudentRev->PNextStudent;
	}

	index=(len-atoi(index_rev)+1);
	while(pIndexStudent){
		if(count==index){
			break;
		}
		pIndexStudent = pIndexStudent->PNextStudent;
		count++;
	}
	if(count == index){
		printf("\tstudent ID : %d\n",pIndexStudent->student.ID);
		printf("\tstudent Name : %s\n",pIndexStudent->student.name);
		printf("\tstudent Leight : %f\n",pIndexStudent->student.leight);
		printf("\t-----------------\n");
	}
	else{
		printf("this index not found in database\n");
	}
}