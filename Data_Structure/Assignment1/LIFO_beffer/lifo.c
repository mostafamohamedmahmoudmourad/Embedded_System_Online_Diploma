/*
 * lifo.c
 *
 *  Created on: 3 Aug 2024
 *      Author: Mostafa Mourad
 */
#include "lifo.h"
#include <stddef.h>
// Initialize the LIFO buffer
LIFO_status LIFO_init(LIFO_BUF_T* lifo_buf, unsigned int* buf, unsigned int length)
{
	// Check if the buffer is NULL
	if(buf == NULL)
		return LIFO_NULL;

	// Initialize the LIFO buffer attributes
	lifo_buf->base = buf;
	lifo_buf->head = buf;
	lifo_buf->length = length;
	lifo_buf->count = 0;

	return LIFO_no_error;
}

// Add an item to the LIFO buffer
LIFO_status LIFO_Add_item(LIFO_BUF_T* lifo_buf, unsigned int item)
{
	// Check if the LIFO buffer is valid
	if (!lifo_buf->base || !lifo_buf->head)
		return LIFO_NULL;

	// Check if the LIFO buffer is full
	if (lifo_buf->count == lifo_buf->length)
		return LIFO_full;

	// Add the item to the buffer
	*(lifo_buf->head) = item;
	lifo_buf->head++;
	lifo_buf->count++;

	return LIFO_no_error;
}

// Get an item from the LIFO buffer
LIFO_status LIFO_get_item(LIFO_BUF_T* lifo_buf, unsigned int* item)
{
	// Check if the LIFO buffer is valid
	if (!lifo_buf->base || !lifo_buf->head)
		return LIFO_NULL;

	// Check if the LIFO buffer is empty
	if (lifo_buf->count == 0)
		return LIFO_empty;

	// Retrieve the item from the buffer
	lifo_buf->head--;
	*item = *(lifo_buf->head);
	lifo_buf->count--;

	return LIFO_no_error;
}

