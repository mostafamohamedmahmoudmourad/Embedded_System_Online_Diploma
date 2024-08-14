/*
 * fifo.c
 *
 *  Created on: 3 Aug 2024
 *  	Author: Mostafa Mourad
 */

#include "fifo.h"
#include <stddef.h>

FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, unsigned int length)
{
	if(buf==NULL)
		return FIFO_NULL;

	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;

	return FIFO_no_error;
}
FIFO_Buf_status FIFO_enqueue (FIFO_Buf_t* fifo, element_type item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;
	if(FIFO_IS_FULL(fifo) == FIFO_full)
		return FIFO_full;

	*(fifo->head)=item;
	fifo->count++;
	if(fifo->head == (fifo->base + (fifo->length * sizeof(element_type))))
		fifo->head=fifo->base;
	else
		fifo->head++;

	return FIFO_no_error;
}
FIFO_Buf_status FIFO_dequeue (FIFO_Buf_t* fifo, element_type* item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;
	if(fifo->count ==0)
		return FIFO_empty;

	*item = *(fifo->tail);
	fifo->count--;

	if(fifo->tail == (fifo->base + (fifo->length * sizeof(element_type))))
		fifo->tail =fifo->base;
	else
		fifo->tail++;

	return FIFO_no_error;
}
FIFO_Buf_status FIFO_IS_FULL (FIFO_Buf_t* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;
	if(fifo->count == fifo->length)
		return FIFO_full;

	return FIFO_no_error;
}

void FIFO_print (FIFO_Buf_t* fifo)
{
	int i = 0;
	element_type* temp;
	if(fifo->count == 0)
	{
		printf("fifo is empty \n");
	}
	else
	{
		temp = fifo->tail;
		printf("\n =========== FIFO_Print======\n");
		for (int i = 0; i < fifo->count; i++)
		{
		    printf("\t %x \n", *temp);
		    if (temp == (fifo->base + fifo->length - 1))
		        temp = fifo->base;
		    else
		        temp++;
		}
	}
	printf("============\n");
}
