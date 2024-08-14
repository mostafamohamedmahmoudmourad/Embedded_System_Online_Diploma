/*
 * lifo.h
 *
 *  Created on: 3 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef LIFO_H_
#define LIFO_H_

// Define the LIFO buffer structure
typedef struct {
    unsigned int length;  // Maximum length of the LIFO buffer
    unsigned int count;   // Current count of items in the LIFO buffer
    unsigned int* base;   // Pointer to the base of the buffer
    unsigned int* head;   // Pointer to the head of the buffer (current top element)
} LIFO_BUF_T;

// Define the LIFO status enumeration
typedef enum {
    LIFO_no_error,  // No error
    LIFO_full,      // LIFO buffer is full
    LIFO_no_full,   // LIFO buffer is not full
    LIFO_empty,     // LIFO buffer is empty
    LIFO_no_empty,  // LIFO buffer is not empty
    LIFO_NULL       // LIFO buffer is NULL
} LIFO_status;

// Function prototypes for LIFO operations

LIFO_status LIFO_init(LIFO_BUF_T* lifo_buf, unsigned int* buf, unsigned int length);
LIFO_status LIFO_Add_item(LIFO_BUF_T* lifo_buf, unsigned int item);
LIFO_status LIFO_get_item(LIFO_BUF_T* lifo_buf, unsigned int* item);


#endif /* LIFO_H_ */

