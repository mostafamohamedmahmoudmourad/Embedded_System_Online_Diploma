/*
 * fifo.h
 *
 *  Created on: 3 Aug 2024
 *      Author: Mostafa Mourad
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include  <stdint.h>

#define element_type 	uint8_t

#define width 	5
element_type uart_buffer[width];

typedef struct {
	element_type* head;
	element_type* base;
	element_type* tail;
	unsigned int length;
	unsigned int count;
}FIFO_Buf_t;


typedef enum {
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_NULL
}FIFO_Buf_status;

FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, unsigned int length);
FIFO_Buf_status FIFO_enqueue (FIFO_Buf_t* fifo, element_type item);
FIFO_Buf_status FIFO_dequeue (FIFO_Buf_t* fifo, element_type* item);
FIFO_Buf_status FIFO_IS_FULL (FIFO_Buf_t* fifo);
void FIFO_print (FIFO_Buf_t* fifo);



#endif /* FIFO_H_ */



