/*
 * FIFO.h
 *
 *  Created on: 15 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdint.h>
#include "StudentManagement.h"

#define element_type    struct sinfo  // Changed to struct sinfo for correct type usage

#define width    5

typedef struct {
    element_type* head;
    element_type* base;
    element_type* tail;
    unsigned int length;
    unsigned int count;
} FIFO_Buf_t;

typedef enum {
    FIFO_no_error,
    FIFO_full,
    FIFO_empty,
    FIFO_NULL
} FIFO_Buf_status;

FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, unsigned int length);
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo, element_type item);
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo, element_type* item);
FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t* fifo);
void FIFO_print(FIFO_Buf_t* fifo);

element_type* FIFO_Find_student_with_rollnumber(FIFO_Buf_t* fifo, int roll);
char FIFO_Find_student_with_fname(FIFO_Buf_t* fifo, char* fname);
char FIFO_Find_students_with_CID(FIFO_Buf_t* fifo, int courseId);
void FIFO_delete_student(FIFO_Buf_t* fifo, element_type* item);

#endif /* FIFO_H_ */
