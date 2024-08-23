/*
 * FIFO.c
 *
 *  Created on: 15 Aug 2024
 *      Author: Mostafa Mourad
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "FIFO.h"
#include "StudentManagement.h"

FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, unsigned int length) {
    if (buf == NULL)
        return FIFO_NULL;

    fifo->base = buf;
    fifo->head = buf;
    fifo->tail = buf;
    fifo->length = length;
    fifo->count = 0;

    return FIFO_no_error;
}

FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo, element_type item) {
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_NULL;
    if (FIFO_IS_FULL(fifo) == FIFO_full)
        return FIFO_full;

    *fifo->head = item;
    fifo->count++;
    if (fifo->head == fifo->base + (fifo->length - 1))
        fifo->head = fifo->base;
    else
        fifo->head++;

    return FIFO_no_error;
}

FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo, element_type* item) {
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_NULL;
    if (fifo->count == 0)
        return FIFO_empty;

    *item = *fifo->tail;
    fifo->count--;
    if (fifo->tail == fifo->base + (fifo->length - 1))
        fifo->tail = fifo->base;
    else
        fifo->tail++;

    return FIFO_no_error;
}



FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t* fifo) {
    if (!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_NULL;
    if (fifo->count == fifo->length)
        return FIFO_full;

    return FIFO_no_error;
}

void FIFO_print(FIFO_Buf_t * fifo)
{
	element_type * temp ;
	if (fifo->count == 0)
	{
		DPRINTF("fifo is empty \n");
	}
	else
	{
		temp = fifo ->tail;
		unsigned char i,j;
		for (i=0 ; i<fifo->count ; i++)
		{
			DPRINTF(" --------------------------------\n");
			DPRINTF("Student first name: %s \n",temp->fname);
			DPRINTF("Student last name: %s \n",temp->lname);
			DPRINTF("Student roll number: %d \n",temp->roll);
			DPRINTF("Student GPA number: %0.1f \n",temp->GPA);
			for(j = 0 ; j < 5 ; j++)
			{
				DPRINTF("The Course ID is: %d \n",temp->cid[j]);
			}
			//circular fifo
			if (temp == fifo->base + (fifo->length -1 ))
				temp = fifo->base;
			else
				temp++;
		}
		DPRINTF(" --------------------------------\n");
	}

}

element_type* FIFO_Find_student_with_rollnumber(FIFO_Buf_t* fifo, int roll) {
    element_type* ptr = fifo->tail;
    for (unsigned char index = 0; index < fifo->count; index++) {
        if (roll == ptr->roll) {
            return ptr;
        } else {
            if (ptr == fifo->base + (fifo->length - 1))
                ptr = fifo->base;
            else
                ptr++;
        }
    }
    return NULL;
}

char FIFO_Find_student_with_fname(FIFO_Buf_t* fifo, char* fname) {
    element_type* ptr = fifo->tail;
    char flag = -1;
    for (unsigned char index = 0; index < fifo->count; index++) {
        if (strcmp(fname, ptr->fname) == 0) {
            flag = 0;
            printf(" --------------------------------\n");
            printf("The Students Details are \n");
            printf("The First name is %s \n", ptr->fname);
            printf("The Last name is %s \n", ptr->lname);
            printf("The Roll Number is %d\n", ptr->roll);
            printf("The GPA is %0.1f \n", ptr->GPA);
            printf("Courses: \n");
            for (unsigned char i = 0; i < 5; i++) {
                printf("The Course ID is: %d \n", ptr->cid[i]);
            }
        }
        if (ptr == fifo->base + (fifo->length - 1))
            ptr = fifo->base;
        else
            ptr++;
    }
    return flag;
}

char FIFO_Find_students_with_CID(FIFO_Buf_t* fifo, int courseId) {
    element_type* ptr = fifo->tail;
    char flag = -1;
    char counter = 0;
    for (unsigned char index = 0; index < fifo->count; index++) {
        for (unsigned char course = 0; course < 5; course++) {
            if (courseId == ptr->cid[course]) {
                flag = 0;
                printf(" --------------------------------\n");
                printf("The Students Details are \n");
                printf("The First name is %s \n", ptr->fname);
                printf("The Last name is %s \n", ptr->lname);
                printf("The Roll Number is %d\n", ptr->roll);
                printf("The GPA is %0.1f \n", ptr->GPA);
                counter++;
                break;
            }
        }
        if (ptr == fifo->base + (fifo->length - 1))
            ptr = fifo->base;
        else
            ptr++;
    }
    if (counter != 0)
        printf(" [INFO] Total Number of Students Enrolled: %d \n", counter);
    return flag;
}

char FIFO_enqueue_specific_info(FIFO_Buf_t* fifo, char index_info, char* token) {
    unsigned char course_index = 0;
    int roll;
    switch (index_info) {
    case ROLL_NUMNBER_INDEX:
        roll = atoi(token);
        if (FIFO_Find_student_with_rollnumber(fifo, roll) != NULL) {
            printf("[ERROR] Roll Number %d is already taken \n", roll);
            return -1;
        } else {
            fifo->head->roll = roll;
        }
        break;
    case F_NAME_INDEX:
        strcpy(fifo->head->fname, token);
        break;
    case L_NAME_INDEX:
        strcpy(fifo->head->lname, token);
        break;
    case GPA_INDEX:
        fifo->head->GPA = atof(token);
        break;
    case CID_INDEX:
        while (token) {
            fifo->head->cid[course_index] = atoi(token);
            course_index++;
            token = strtok(NULL, " ");
        }
        printf("[INFO] Roll Number %d saved successfully\n", fifo->head->roll);
        // Circular FIFO
        if (fifo->head == fifo->base + (fifo->length - 1))
            fifo->head = fifo->base;
        else
            fifo->head++;
        fifo->count++;
        break;
    }
    return 0;
}

void FIFO_delete_student(FIFO_Buf_t* fifo, element_type* item) {
    element_type* ptrNext = fifo->tail;
    while (ptrNext != fifo->head) {
        if (ptrNext == fifo->base + (fifo->length - 1))
            ptrNext = fifo->base;
        else
            ptrNext++;
        if (ptrNext == fifo->head) {
            printf("[ERROR] Student not found\n");
            return;
        }
    }
    element_type* ptrPrev = fifo->tail;
    while (ptrPrev != fifo->head) {
        if (ptrPrev == fifo->base + (fifo->length - 1))
            ptrPrev = fifo->base;
        else
            ptrPrev++;
        if (ptrPrev == fifo->head) {
            if (fifo->tail == fifo->base + (fifo->length - 1))
                fifo->tail = fifo->base;
            else
                fifo->tail++;
            fifo->count--;
            printf("[INFO] Student with Roll Number %d deleted successfully\n", item->roll);
            return;
        }
    }
}
