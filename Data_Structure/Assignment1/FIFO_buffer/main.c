/*
 * main.c
 *
 *  Created on: 3 Aug 2024
 *      Author: Mostafa Mourad
 */


#include "fifo.h"

int main()
{
	element_type i , temp=0;
	FIFO_Buf_t FIFO_UART;
	if(FIFO_init(&FIFO_UART, uart_buffer, 5) == FIFO_no_error)
		printf("FIFO init -----Done \n");
	for(i=0; i<7; i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue(&FIFO_UART, i) == FIFO_no_error)
			printf("\t FIFO Enqueue -----Done \n");
		else
			printf("\t FIFO Enqueue -----Failed \n");
	}
	FIFO_print(&FIFO_UART);
	if(FIFO_dequeue(&FIFO_UART, &temp) == FIFO_no_error)
		printf("FIFO Dequeue %x -----Done \n",temp);
	if(FIFO_dequeue(&FIFO_UART, &temp) == FIFO_no_error)
			printf("FIFO Dequeue %x -----Done \n",temp);
	FIFO_print(&FIFO_UART);

	return 0;
}
