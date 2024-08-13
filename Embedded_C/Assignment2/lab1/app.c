#include "uart.h"

unsigned char string_buffer[100]="Learn_in_depth: Mostafa";
// unsigned char const string_buffer2[100]="Learn_in_depth: Mostafa";


void main()
{
    Uart_Send_String(string_buffer);
}