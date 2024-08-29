/*
 * GccApplication1.c
 *
 * Created: 27/08/2024 20:13:19
 * Author : Mostafa Mourad
 */ 

#define F_CPU	80000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void InterruptInit()
{
	//Any logical change on INT0 generates an interrupt request.
	MCUCR |=  (1<<ISC00);
	MCUCR &= ~(1<<ISC01);
	
	//The rising edge of INT1 generates an interrupt request.
	MCUCR |= (1<<ISC10) | (1<<ISC11);
	
	//The falling edge of INT2 generates an interrupt request.
	MCUCR &= ~(1<<ISC2);
	
	//Enable INT0, INT1, INT2.
	GICR |= (1<<INT0) | (1<<INT1) | (1<<INT2);
	
	 //Global Interrupt Enable
	 //The I-bit can also be setand cleared by the application with the SEI and CLI instructions,
	 sei();
}

int main(void)
{
	//Set Data Direction.
	DDRD = 0b11100000;	// Set PD5, PD6 AND PD7  Output
	
	InterruptInit();	

    while (1) 
    {
    }
}

ISR(INT0_vect)
{
	PORTD |= (1<<PD5);		//Turn on LED connected to PD5.
	_delay_ms(1000);		//Delay for One Second.
	PORTD &= ~(1<<PD5);		//Turn off LED connected to PD5.
}

ISR(INT1_vect)
{
	PORTD |= (1<<PD6);		//Turn on LED connected to PD6.
	_delay_ms(1000);		//Delay for One Second.
	PORTD &= ~(1<<PD6);		//Turn off LED connected to PD6.
}

ISR(INT2_vect)
{
	PORTD |= (1<<PD7);		//Turn on LED connected to PD7.
	_delay_ms(1000);		//Waiting 1 Second.
	PORTD &= ~(1<<PD7);		//Turn off LED connected to PD7.
}