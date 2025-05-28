
/*
#define F_CPU 16000000UL  // ?????? 16 ????????
#include <avr/io.h>
#include <util/delay.h>

// ????? ?????? LCD ????? ??? ???????
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define LCD_RS PC4
#define LCD_RW PC5
#define LCD_EN PC6
#define LCD_D4 PC0
#define LCD_D5 PC1
#define LCD_D6 PC2
#define LCD_D7 PC3

// ????? ???????? ??????
#define LED_PIN PB0      // ???? ??? LED
#define BUTTON_PIN PB1   // ???? ????
#define BUZZER_PIN PB2   // ???? ???uzzer
#define FAN_PIN PD4      // ???? ??????? (OC2 ?? PWM)

// ?????? ?????????
void LCD_init(void);          // ????? LCD
void LCD_command(unsigned char cmd);  // ????? ??? ?? LCD
void LCD_data(unsigned char data);    // ????? ?????? ?? LCD
void LCD_string(char *str);   // ??? ?? ??? LCD
void ADC_init(void);          // ????? ADC
void PWM_init(void);          // ????? PWM
uint16_t ADC_read(uint8_t channel);  // ????? ???? ADC

// ????? LCD
void LCD_init(void) {
	LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7); // ????? ?????? LCD ???????
	LCD_PORT &= ~(1 << LCD_RW);  // ??? RW ??? 0 (??? ???????)
	_delay_ms(50);  // ???????? ?????? LCD
	
	// ????? LCD ?? ??? 4 ??
	LCD_command(0x02);  // ?????? ??????
	_delay_ms(5);
	LCD_command(0x28);  // ??? 4 ??? ?????? ?? 5x8
	_delay_ms(5);
	LCD_command(0x0C);  // ????? ?????? ????? ??????
	_delay_ms(5);
	LCD_command(0x06);  // ??? ???????: ?????? ???? ?????
	_delay_ms(5);
	LCD_command(0x01);  // ??? ?????
	_delay_ms(5);
}

// ????? ??? ?? LCD
void LCD_command(unsigned char cmd) {
	LCD_PORT &= ~(1 << LCD_RS);  // RS = 0 ???????
	LCD_PORT &= ~(1 << LCD_RW);  // RW = 0 ???????
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);
}

// ????? ?????? ?? LCD
void LCD_data(unsigned char data) {
	LCD_PORT |= (1 << LCD_RS);  // RS = 1 ????????
	LCD_PORT &= ~(1 << LCD_RW);  // RW = 0 ???????
	LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	
	LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);
}

// ??? ?? ??? LCD
void LCD_string(char *str) {
	while (*str) {
		LCD_data(*str++);
	}
}

// ????? ADC
void ADC_init(void) {
	ADMUX = (1 << REFS0);  // ????? ??????? = AVCC (5V)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // ????? ADC? ???? ?????? = 128
}

// ????? ???? ?? ???? ADC
uint16_t ADC_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // ?????? ???? ADC
	ADCSRA |= (1 << ADSC);  // ??? ???????
	while (ADCSRA & (1 << ADSC));  // ???????? ??? ????? ???????
	return ADC;
}

// ????? PWM (Timer 2 ??? OC2/PD4)
void PWM_init(void) {
	DDRD |= (1 << FAN_PIN);  // ????? PD4 ?????
	// ??? Fast PWM? ??? ?????? ???? ???? = 8
	// ?????? = F_CPU / (prescaler * 256) = 16MHz / (8 * 256) = 7.8125 kHz
	TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21);
	OCR2 = 0;  // ???? ????? ???????? = 0% (??????? ?????)
}

int main(void) {
	// ????? ????????
	DDRB |= (1 << LED_PIN) | (1 << BUZZER_PIN);  // ????? ?????? LED ? buzzer ???????
	DDRB &= ~(1 << BUTTON_PIN);  // ????? ???? ???? ?????
	
	PORTB &= ~(1 << LED_PIN);  // ????? ??? LED ???????
	PORTB &= ~(1 << BUZZER_PIN);  // ????? ???uzzer ???????
	
	// ????? ??????? ???????
	LCD_init();  // ????? LCD
	ADC_init();  // ????? ADC
	PWM_init();  // ????? PWM
	
	// ??? ??????? ??????? ??? LCD
	LCD_command(0x01);  // ??? ?????
	LCD_string("Temp: ");
	
	while (1) {
		// ????? ???? ??????? ?? LM35 (???? ?? ADC0/PA0)
		uint16_t adc_value = ADC_read(0);  // ????? ADC0
		float voltage = (adc_value * 5.0) / 1023.0;  // ????? ??? ??? (???? 5V)
		float temperature = voltage * 100.0;  // LM35: 10mV/°C? ?? ????? * 100 = ???? ??????? ????????
		
		// ??? ???? ??????? ??? LCD
		LCD_command(0x80 + 6);  // ????? ?????? ??? ?????? ??? "Temp: "
		char temp_str[10];
		sprintf(temp_str, "%.1f C", temperature);
		LCD_string(temp_str);
		
		// ?????? ?? ???? ??????? ????? ??? ???? ???????
		if (temperature < 25.0) {
			OCR2 = 0;  // ??????? ????? (???? ????? 0%)
			} else if (temperature >= 25.0 && temperature < 30.0) {
			OCR2 = 127;  // ???? 50% (???? ????? 50%)
			} else if (temperature >= 30.0) {
			OCR2 = 255;  // ???? 100% (???? ????? 100%)
		}
		
		// ?????? ????????: ????? ???uzzer ? ??? LED ??? ?????? ???? ??????? 35 ?????
		if (temperature > 35.0) {
			PORTB |= (1 << LED_PIN);  // ????? ??? LED
			PORTB |= (1 << BUZZER_PIN);  // ????? ???uzzer
			} else {
			PORTB &= ~(1 << LED_PIN);  // ????? ??? LED
			PORTB &= ~(1 << BUZZER_PIN);  // ????? ???uzzer
		}
		
		// ?????? ?? ??? ???? (?????? ?????? ?? ???????)
		if (PINB & (1 << BUTTON_PIN)) {
			if (OCR2 == 0) {
				OCR2 = 255;  // ????? ??????? ????? 100% ??? ???? ?????
				} else {
				OCR2 = 0;  // ????? ??????? ??? ???? ????
			}
			_delay_ms(200);  // ????? ???? ??????? (debounce)
		}
		
		_delay_ms(500);  // ????? ?? 500 ???? ?????
	}
	
	return 0;
}

*/


/*

#define F_CPU 16000000UL  // ?????? 16 ????????
#include <avr/io.h>
#include <util/delay.h>

// ????? ?????? LCD ????? ??? ???????
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define LCD_RS PC4
#define LCD_RW PC5
#define LCD_EN PC6
#define LCD_D4 PC0
#define LCD_D5 PC1
#define LCD_D6 PC2
#define LCD_D7 PC3

// ????? ???????? ??????
#define LED_PIN PB0      // ???? ??? LED
#define BUTTON_PIN PB1   // ???? ????
#define BUZZER_PIN PB2   // ???? ???uzzer
#define FAN_PIN PD4      // ???? ??????? (OC2 ?? PWM)

// ?????? ?????????
void LCD_init(void);          // ????? LCD
void LCD_command(unsigned char cmd);  // ????? ??? ?? LCD
void LCD_data(unsigned char data);    // ????? ?????? ?? LCD
void LCD_string(char *str);   // ??? ?? ??? LCD
void ADC_init(void);          // ????? ADC
void PWM_init(void);          // ????? PWM
uint16_t ADC_read(uint8_t channel);  // ????? ???? ADC

// ????? LCD
void LCD_init(void) {
	LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7); // ????? ?????? LCD ???????
	LCD_PORT &= ~(1 << LCD_RW);  // ??? RW ??? 0 (??? ???????)
	_delay_ms(50);  // ???????? ?????? LCD
	
	// ????? LCD ?? ??? 4 ??
	LCD_command(0x02);  // ?????? ??????
	_delay_ms(5);
	LCD_command(0x28);  // ??? 4 ??? ?????? ?? 5x8
	_delay_ms(5);
	LCD_command(0x0C);  // ????? ?????? ????? ??????
	_delay_ms(5);
	LCD_command(0x06);  // ??? ???????: ?????? ???? ?????
	_delay_ms(5);
	LCD_command(0x01);  // ??? ?????
	_delay_ms(5);
}

// ????? ??? ?? LCD
void LCD_command(unsigned char cmd) {
	LCD_PORT &= ~(1 << LCD_RS);  // RS = 0 ???????
	LCD_PORT &= ~(1 << LCD_RW);  // RW = 0 ???????
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);
}

// ????? ?????? ?? LCD
void LCD_data(unsigned char data) {
	LCD_PORT |= (1 << LCD_RS);  // RS = 1 ????????
	LCD_PORT &= ~(1 << LCD_RW);  // RW = 0 ???????
	LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	
	LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);
}

// ??? ?? ??? LCD
void LCD_string(char *str) {
	while (*str) {
		LCD_data(*str++);
	}
}

// ????? ADC
void ADC_init(void) {
	ADMUX = (1 << REFS0);  // ????? ??????? = AVCC (5V)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // ????? ADC? ???? ?????? = 128
}

// ????? ???? ?? ???? ADC
uint16_t ADC_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // ?????? ???? ADC
	ADCSRA |= (1 << ADSC);  // ??? ???????
	while (ADCSRA & (1 << ADSC));  // ???????? ??? ????? ???????
	return ADC;  // ????? ?????? ????????
}

// ????? PWM (Timer 2 ??? OC2/PD4)
void PWM_init(void) {
	DDRD |= (1 << FAN_PIN);  // ????? PD4 ?????
	// ??? Fast PWM? ??? ?????? ???? ???? = 8
	// ?????? = F_CPU / (prescaler * 256) = 16MHz / (8 * 256) = 7.8125 kHz
	TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21);
	OCR2 = 0;  // ???? ????? ???????? = 0% (??????? ?????)
}

int main(void) {
	// ????? ????????
	DDRB |= (1 << LED_PIN) | (1 << BUZZER_PIN);  // ????? ?????? LED ? buzzer ???????
	DDRB &= ~(1 << BUTTON_PIN);  // ????? ???? ???? ?????
	
	PORTB &= ~(1 << LED_PIN);  // ????? ??? LED ???????
	PORTB &= ~(1 << BUZZER_PIN);  // ????? ???uzzer ???????
	
	// ????? ??????? ???????
	LCD_init();  // ????? LCD
	ADC_init();  // ????? ADC
	PWM_init();  // ????? PWM
	
	// ??? ??????? ??????? ??? LCD
	LCD_command(0x01);  // ??? ?????
	LCD_string("Temp: ");
	
	while (1) {
		// ????? ???? ??????? ?? LM35 (???? ?? ADC0/PA0)
		uint16_t adc_value = ADC_read(0);  // ????? ADC0
		float voltage = (adc_value * 5.0) / 1023.0;  // ????? ??? ??? (???? 5V)
		float temperature = voltage * 100.0;  // LM35: 10mV/°C? ?? ????? * 100 = ???? ??????? ????????
		
		// ??? ???? ??????? ??? LCD
		LCD_command(0x80 + 6);  // ????? ?????? ??? ?????? ??? "Temp: " (?????? 7)
		char temp_str[10];
		if (adc_value > 0) {  // ???? ??? ???? ??????? ?????
			sprintf(temp_str, "%.1f C", temperature);  // ????? ???? ??????? ??? ??
			} else {
			sprintf(temp_str, "ERR");  // ??? "ERR" ??? ???? ??????? ??? ?????
		}
		LCD_string(temp_str);
		
		// ?????? ?? ???? ??????? ????? ??? ???? ???????
		if (temperature < 25.0) {
			OCR2 = 0;  // ??????? ????? (???? ????? 0%)
			} else if (temperature >= 25.0 && temperature < 30.0) {
			OCR2 = 127;  // ???? 50% (???? ????? 50%)
			} else if (temperature >= 30.0) {
			OCR2 = 255;  // ???? 100% (???? ????? 100%)
		}
		
		// ?????? ????????: ????? ???uzzer ? ??? LED ??? ?????? ???? ??????? 35 ?????
		if (temperature > 35.0) {
			PORTB |= (1 << LED_PIN);  // ????? ??? LED
			PORTB |= (1 << BUZZER_PIN);  // ????? ???uzzer
			} else {
			PORTB &= ~(1 << LED_PIN);  // ????? ??? LED
			PORTB &= ~(1 << BUZZER_PIN);  // ????? ???uzzer
		}
		
		// ?????? ?? ??? ???? (?????? ?????? ?? ???????)
		if (PINB & (1 << BUTTON_PIN)) {
			if (OCR2 == 0) {
				OCR2 = 255;  // ????? ??????? ????? 100% ??? ???? ?????
				} else {
				OCR2 = 0;  // ????? ??????? ??? ???? ????
			}
			_delay_ms(200);  // ????? ???? ??????? (debounce)
		}
		
		_delay_ms(500);  // ????? ?? 500 ???? ?????
	}
	
	return 0;
}


*/

/*


#define F_CPU 16000000UL  // ?????? 16 ????????
#include <avr/io.h>
#include <util/delay.h>

// ????? ?????? LCD ????? ??? ???????
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define LCD_RS PC4
#define LCD_RW PC5
#define LCD_EN PC6
#define LCD_D4 PC0
#define LCD_D5 PC1
#define LCD_D6 PC2
#define LCD_D7 PC3

// ????? ???????? ??????
#define LED_PIN PB0      // ???? ??? LED
#define BUTTON_PIN PB1   // ???? ????
#define BUZZER_PIN PB2   // ???? ???uzzer
#define FAN_PIN PD4      // ???? ??????? (OC2 ?? PWM)

// ?????? ?????????
void LCD_init(void);          // ????? LCD
void LCD_command(unsigned char cmd);  // ????? ??? ?? LCD
void LCD_data(unsigned char data);    // ????? ?????? ?? LCD
void LCD_string(char *str);   // ??? ?? ??? LCD
void ADC_init(void);          // ????? ADC
void PWM_init(void);          // ????? PWM
uint16_t ADC_read(uint8_t channel);  // ????? ???? ADC
void display_number(float number);   // ???? ???? ????? ??? LCD

// ????? LCD
void LCD_init(void) {
	LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7); // ????? ?????? LCD ???????
	LCD_PORT &= ~(1 << LCD_RW);  // ??? RW ??? 0 (??? ???????)
	_delay_ms(50);  // ???????? ?????? LCD
	
	// ????? LCD ?? ??? 4 ??
	LCD_command(0x02);  // ?????? ??????
	_delay_ms(5);
	LCD_command(0x28);  // ??? 4 ??? ?????? ?? 5x8
	_delay_ms(5);
	LCD_command(0x0C);  // ????? ?????? ????? ??????
	_delay_ms(5);
	LCD_command(0x06);  // ??? ???????: ?????? ???? ?????
	_delay_ms(5);
	LCD_command(0x01);  // ??? ?????
	_delay_ms(5);
}

// ????? ??? ?? LCD
void LCD_command(unsigned char cmd) {
	LCD_PORT &= ~(1 << LCD_RS);  // RS = 0 ???????
	LCD_PORT &= ~(1 << LCD_RW);  // RW = 0 ???????
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);
}

// ????? ?????? ?? LCD
void LCD_data(unsigned char data) {
	LCD_PORT |= (1 << LCD_RS);  // RS = 1 ????????
	LCD_PORT &= ~(1 << LCD_RW);  // RW = 0 ???????
	LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	
	LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F);  // ????? ????? ??????
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);
}

// ??? ?? ??? LCD
void LCD_string(char *str) {
	while (*str) {
		LCD_data(*str++);
	}
}

// ????? ADC
void ADC_init(void) {
	ADMUX = (1 << REFS0);  // ????? ??????? = AVCC (5V)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // ????? ADC? ???? ?????? = 128
}

// ????? ???? ?? ???? ADC
uint16_t ADC_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // ?????? ???? ADC
	ADCSRA |= (1 << ADSC);  // ??? ???????
	while (ADCSRA & (1 << ADSC));  // ???????? ??? ????? ???????
	return ADC;  // ????? ?????? ????????
}

// ????? PWM (Timer 2 ??? OC2/PD4)
void PWM_init(void) {
	DDRD |= (1 << FAN_PIN);  // ????? PD4 ?????
	// ??? Fast PWM? ??? ?????? ???? ???? = 8
	// ?????? = F_CPU / (prescaler * 256) = 16MHz / (8 * 256) = 7.8125 kHz
	TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21);
	OCR2 = 0;  // ???? ????? ???????? = 0% (??????? ?????)
}

// ???? ???? ????? ??? LCD
void display_number(float number) {
	int temp_int = (int)(number * 10);  // ????? ??? ??? ???? ??????? ?? 10 (??? 42.0 ? 420)
	int integer_part = temp_int / 10;   // ????? ?????? (42)
	int decimal_part = temp_int % 10;   // ????? ?????? (0)

	// ??? ????? ??????
	if (integer_part > 99) LCD_data(integer_part / 100 + '0');  // ????
	if (integer_part > 9) LCD_data((integer_part / 10) % 10 + '0');  // ?????
	LCD_data(integer_part % 10 + '0');  // ???????

	// ??? ?????? ???????
	LCD_data('.');

	// ??? ????? ??????
	LCD_data(decimal_part + '0');
}

// ?????? ????????
int main(void) {
	// ????? ????????
	DDRB |= (1 << LED_PIN) | (1 << BUZZER_PIN);  // ????? ?????? LED ? buzzer ???????
	DDRB &= ~(1 << BUTTON_PIN);  // ????? ???? ???? ?????
	
	PORTB &= ~(1 << LED_PIN);  // ????? ??? LED ???????
	PORTB &= ~(1 << BUZZER_PIN);  // ????? ???uzzer ???????
	
	// ????? ??????? ???????
	LCD_init();  // ????? LCD
	ADC_init();  // ????? ADC
	PWM_init();  // ????? PWM
	
	// ??? ??????? ??????? ??? LCD
	LCD_command(0x01);  // ??? ?????
	LCD_string("Temp: ");
	
	while (1) {
		// ????? ???? ??????? ?? LM35 (???? ?? ADC0/PA0)
		uint16_t adc_value = ADC_read(0);  // ????? ADC0
		float voltage = (adc_value * 5.0) / 1023.0;  // ????? ??? ??? (???? 5V)
		float temperature = voltage * 100.0;  // LM35: 10mV/°C? ?? ????? * 100 = ???? ??????? ????????
		
		// ??? ???? ??????? ??? LCD
		LCD_command(0x80 + 6);  // ????? ?????? ??? ?????? ??? "Temp: " (?????? 7)
		if (adc_value > 0 && adc_value < 1023) {  // ???? ?? ?? ??????? ?????
			display_number(temperature);  // ??? ???? ???????
			LCD_string(" C");  // ????? "C"
			} else {
			LCD_string("ERR");  // ??? "ERR" ??? ???? ??????? ??? ?????
		}
		
		// ?????? ?? ???? ??????? ????? ??? ???? ???????
		if (temperature < 25.0) {
			OCR2 = 0;  // ??????? ????? (???? ????? 0%)
			} else if (temperature >= 25.0 && temperature < 30.0) {
			OCR2 = 127;  // ???? 50% (???? ????? 50%)
			} else if (temperature >= 30.0) {
			OCR2 = 255;  // ???? 100% (???? ????? 100%)
		}
		
		// ?????? ????????: ????? ???uzzer ? ??? LED ??? ?????? ???? ??????? 35 ?????
		if (temperature > 35.0) {
			PORTB |= (1 << LED_PIN);  // ????? ??? LED
			PORTB |= (1 << BUZZER_PIN);  // ????? ???uzzer
			} else {
			PORTB &= ~(1 << LED_PIN);  // ????? ??? LED
			PORTB &= ~(1 << BUZZER_PIN);  // ????? ???uzzer
		}
		
		// ?????? ?? ??? ???? (?????? ?????? ?? ???????)
		if (PINB & (1 << BUTTON_PIN)) {
			if (OCR2 == 0) {
				OCR2 = 255;  // ????? ??????? ????? 100% ??? ???? ?????
				} else {
				OCR2 = 0;  // ????? ??????? ??? ???? ????
			}
			_delay_ms(200);  // ????? ???? ??????? (debounce)
		}
		
		_delay_ms(500);  // ????? ?? 500 ???? ?????
	}
	
	return 0;
}

*/

/******************************************************************************************
#define F_CPU 16000000UL  // ?????? 16 ????????
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ????? ?????? LCD ????? ??? ??????? ???????
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define LCD_RS PC4
#define LCD_RW PC5
#define LCD_EN PC6
#define LCD_D4 PC0
#define LCD_D5 PC1
#define LCD_D6 PC2
#define LCD_D7 PC3

// ????? ???????? ??????
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PB0      // ???? ??? LED
#define BUTTON_PORT PORTB
#define BUTTON_DDR DDRB
#define BUTTON_PIN PINB
#define BUTTON_MANUAL PB1   // ???? ???? ??????
#define BUZZER_PORT PORTB
#define BUZZER_DDR DDRB
#define BUZZER_PIN PB2   // ???? ??????
#define FAN_PWM_PORT PORTD
#define FAN_PWM_DDR DDRD
#define FAN_PWM_PIN PD4  // ???? ??????? (OC2 ?? PWM)
#define BUTTON1 PD2      // ?? ??? ??????? (INT0)
#define BUTTON2 PD3      // ?? ????? ??????? (INT1)

// Temperature Thresholds
volatile uint8_t threshold_low = 25;  // Default low threshold (25°C)
volatile uint8_t threshold_high = 30; // Default high threshold (30°C)
volatile uint8_t threshold_critical = 35; // Default critical threshold (35°C)

// Function Prototypes
void LCD_init(void);
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_string(const char *str);
void ADC_init(void);
void PWM_init(void);
void set_fan_speed(uint8_t duty_cycle);
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
void LED_init(void);
void LED_on(void);
void LED_off(void);
void Button_init(void);
void display_temperature(float temp);

// Global Variables
volatile uint16_t adc_value = 0;
volatile float temperature = 0.0;
volatile uint8_t setting_mode = 0; // 0: Normal, 1: Set low, 2: Set high, 3: Set critical
volatile uint8_t manual_fan = 0;   // 0: Auto, 1: Manual (on/off)

// ADC Interrupt Service Routine
ISR(ADC_vect) {
    adc_value = ADC; // Read ADC value
    float voltage = (adc_value * 5.0) / 1023.0; // ????? ??? ??? (???? 5V)
    temperature = voltage * 100.0; // LM35: 10mV/°C
    
    // Fan Control Logic (Auto mode)
    if (!manual_fan) {
        if (temperature < threshold_low) {
            set_fan_speed(0); // Fan off
        } else if (temperature >= threshold_low && temperature < threshold_high) {
            set_fan_speed(127); // 50% speed
        } else {
            set_fan_speed(255); // 100% speed
        }
    }
    
    // Buzzer and LED Control
    if (temperature >= threshold_critical) {
        Buzzer_on();
        LED_on();
    } else {
        Buzzer_off();
        LED_off();
    }
    
    // Restart ADC conversion
    ADCSRA |= (1 << ADSC);
}

// INT0 ISR (Button1: Enter/Exit setting mode or confirm)
ISR(INT0_vect) {
    _delay_ms(50); // Debounce
    if (!(PIND & (1 << BUTTON1))) {
        if (setting_mode == 0) {
            setting_mode = 1; // Enter setting mode (low threshold)
        } else {
            setting_mode = (setting_mode + 1) % 4; // Cycle through modes or exit
        }
    }
}

// INT1 ISR (Button2: Increment threshold)
ISR(INT1_vect) {
    _delay_ms(50); // Debounce
    if (!(PIND & (1 << BUTTON2))) {
        if (setting_mode == 1) {
            threshold_low = (threshold_low < 40) ? threshold_low + 1 : threshold_low;
        } else if (setting_mode == 2) {
            threshold_high = (threshold_high < 50) ? threshold_high + 1 : threshold_high;
        } else if (setting_mode == 3) {
            threshold_critical = (threshold_critical < 60) ? threshold_critical + 1 : threshold_critical;
        }
    }
}

int main(void) {
    // Initialize peripherals
    LCD_init();
    ADC_init();
    PWM_init();
    Buzzer_init();
    LED_init();
    Button_init();
    
    // Enable global interrupts
    sei();
    
    // Display startup message
    LCD_command(0x01); // Clear display
    LCD_string("Temp: --.- C");
    
    while (1) {
        // Check manual fan control button (PB1)
        if (BUTTON_PIN & (1 << BUTTON_MANUAL)) {
            _delay_ms(200); // Debounce
            if (BUTTON_PIN & (1 << BUTTON_MANUAL)) {
                manual_fan = !manual_fan; // Toggle manual mode
                if (manual_fan) {
                    set_fan_speed(255); // Fan on (100%)
                } else {
                    set_fan_speed(0); // Return to auto mode
                }
            }
        }
        
        if (setting_mode == 0) {
            // Normal mode: Display temperature
            display_temperature(temperature);
        } else {
            // Setting mode: Display thresholds
            LCD_command(0x01); // Clear display
            if (setting_mode == 1) {
                LCD_string("Set Low: ");
                LCD_data((threshold_low / 10) + '0');
                LCD_data((threshold_low % 10) + '0');
                LCD_string(" C");
            } else if (setting_mode == 2) {
                LCD_string("Set High: ");
                LCD_data((threshold_high / 10) + '0');
                LCD_data((threshold_high % 10) + '0');
                LCD_string(" C");
            } else if (setting_mode == 3) {
                LCD_string("Set Crit: ");
                LCD_data((threshold_critical / 10) + '0');
                LCD_data((threshold_critical % 10) + '0');
                LCD_string(" C");
            }
            _delay_ms(500);
        }
        
        _delay_ms(100); // ????? ????
    }
}

// LCD Initialization (4-bit mode)
void LCD_init(void) {
    LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0 (write mode)
    _delay_ms(50);
    LCD_command(0x02); // 4-bit mode
    LCD_command(0x28); // 2 lines, 5x8 font
    LCD_command(0x0C); // Display on, cursor off
    LCD_command(0x06); // Increment cursor
    LCD_command(0x01); // Clear display
    _delay_ms(5);
}

// Send command to LCD
void LCD_command(uint8_t cmd) {
    LCD_PORT &= ~(1 << LCD_RS); // RS = 0
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Send data to LCD
void LCD_data(uint8_t data) {
    LCD_PORT |= (1 << LCD_RS); // RS = 1
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Display string on LCD
void LCD_string(const char *str) {
    while (*str) {
        LCD_data(*str++);
    }
}

// ADC Initialization
void ADC_init(void) {
    ADMUX = (1 << REFS0); // AVCC with external capacitor at AREF
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, interrupt, prescaler 128
    ADCSRA |= (1 << ADSC); // Start first conversion
}

// PWM Initialization (Timer2, Fast PWM for Fan Control via Transistor)

void PWM_init(void) {
    FAN_PWM_DDR |= (1 << FAN_PWM_PIN); // Set PD4 (OC2) as output
    TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21); // Fast PWM, non-inverted, prescaler 8
    OCR2 = 0; // Initial duty cycle 0% (fan off)
}

// Set fan speed (0-255) via PWM to control transistor
void set_fan_speed(uint8_t duty_cycle) {
    OCR2 = duty_cycle; // Set PWM duty cycle (0 = off, 127 = 50%, 255 = 100%)
}

// Buzzer Initialization
void Buzzer_init(void) {
    BUZZER_DDR |= (1 << BUZZER_PIN);
    Buzzer_off();
}

// Turn buzzer on
void Buzzer_on(void) {
    BUZZER_PORT |= (1 << BUZZER_PIN);
}

// Turn buzzer off
void Buzzer_off(void) {
    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

// LED Initialization
void LED_init(void) {
    LED_DDR |= (1 << LED_PIN);
    LED_off();
}

// Turn LED on
void LED_on(void) {
    LED_PORT |= (1 << LED_PIN);
}

// Turn LED off
void LED_off(void) {
    LED_PORT &= ~(1 << LED_PIN);
}

// Button Initialization (External Interrupts + Manual Button)
void Button_init(void) {
    BUTTON_DDR &= ~((1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON_MANUAL)); // Inputs
    PORTD |= (1 << BUTTON1) | (1 << BUTTON2); // Enable pull-ups for INT0, INT1
    PORTB |= (1 << BUTTON_MANUAL); // Enable pull-up for manual button
    GICR |= (1 << INT0) | (1 << INT1); // Enable INT0, INT1
    MCUCR |= (1 << ISC01) | (1 << ISC11); // Falling edge
}

// Display temperature on LCD
void display_temperature(float temp) {
    LCD_command(0x80); // Move to first line
    LCD_string("Temp: ");
    int temp_int = (int)(temp * 10);
    int integer_part = temp_int / 10;
    int decimal_part = temp_int % 10;
    if (integer_part > 99) LCD_data(integer_part / 100 + '0');
    if (integer_part > 9) LCD_data((integer_part / 10) % 10 + '0');
    LCD_data(integer_part % 10 + '0');
    LCD_data('.');
    LCD_data(decimal_part + '0');
    LCD_string(" C");
}
*/


/** *  ** * * * * * *  **  ** * * * * * * ** * * *****************************************              *********************
#define F_CPU 16000000UL  // ?????? 16 ????????
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ????? ?????? LCD ????? ??? ???????
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define LCD_RS PC4
#define LCD_RW PC5
#define LCD_EN PC6
#define LCD_D4 PC0
#define LCD_D5 PC1
#define LCD_D6 PC2
#define LCD_D7 PC3

// ????? ???????? ??????
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PB0      // ???? ??? LED
#define BUTTON_PORT PORTB
#define BUTTON_DDR DDRB
#define BUTTON_PIN PINB
#define BUTTON_MANUAL PB1   // ???? ???? ??????
#define BUZZER_PORT PORTB
#define BUZZER_DDR DDRB
#define BUZZER_PIN PB2   // ???? ??????
#define FAN_PWM_PORT PORTD
#define FAN_PWM_DDR DDRD
#define FAN_PWM_PIN PD7  // ???? ??????? (OC2 ?? PWM)

// Temperature Thresholds
volatile uint8_t threshold_low = 25;  // Default low threshold (25°C)
volatile uint8_t threshold_high = 30; // Default high threshold (30°C)
volatile uint8_t threshold_critical = 35; // Default critical threshold (35°C)

// Function Prototypes
void LCD_init(void);
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_string(const char *str);
void ADC_init(void);
void PWM_init(void);
void set_fan_speed(uint8_t duty_cycle);
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
void LED_init(void);
void LED_on(void);
void LED_off(void);
void Button_init(void);
void display_temperature(float temp);

// Global Variables
volatile uint16_t adc_value = 0;
volatile float temperature = 0.0;
volatile uint8_t manual_fan = 0;   // 0: Auto, 1: Manual (on/off)

// ADC Interrupt Service Routine
ISR(ADC_vect) {
    adc_value = ADC; // Read ADC value
    float voltage = (adc_value * 5.0) / 1023.0; // ????? ??? ??? (???? 5V)
    temperature = voltage * 100.0; // LM35: 10mV/°C
    
    // Fan Control Logic (Auto mode)
    if (!manual_fan) {
        if (temperature < threshold_low) {
            set_fan_speed(0); // Fan off
        } else if (temperature >= threshold_low && temperature < threshold_high) {
            set_fan_speed(127); // 50% speed
        } else {
            set_fan_speed(255); // 100% speed
        }
    }
    
    // Buzzer and LED Control
    if (temperature >= threshold_critical) {
        Buzzer_on();
        LED_on();
    } else {
        Buzzer_off();
        LED_off();
    }
    
    // Restart ADC conversion
    ADCSRA |= (1 << ADSC);
}

int main(void) {
    // Initialize peripherals
    LCD_init();
    ADC_init();
    PWM_init();
    Buzzer_init();
    LED_init();
    Button_init();
    
    // Enable global interrupts
    sei();
    
    // Display startup message
    LCD_command(0x01); // Clear display
    LCD_string("Temp: --.- C");
    
    while (1) {
        // Check manual fan control button (PB1)
        if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) { // Active-low
            _delay_ms(200); // Debounce
            if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) {
                manual_fan = !manual_fan; // Toggle manual mode
                if (manual_fan) {
                    set_fan_speed(255); // Fan on (100%)
                } else {
                    set_fan_speed(0); // Return to auto mode
                }
            }
        }
        
        // Normal mode: Display temperature
        display_temperature(temperature);
        
        _delay_ms(100); // ????? ????
    }
}

// LCD Initialization (4-bit mode)
void LCD_init(void) {
    LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0 (write mode)
    _delay_ms(50);
    LCD_command(0x02); // 4-bit mode
    LCD_command(0x28); // 2 lines, 5x8 font
    LCD_command(0x0C); // Display on, cursor off
    LCD_command(0x06); // Increment cursor
    LCD_command(0x01); // Clear display
    _delay_ms(5);
}

// Send command to LCD
void LCD_command(uint8_t cmd) {
    LCD_PORT &= ~(1 << LCD_RS); // RS = 0
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Send data to LCD
void LCD_data(uint8_t data) {
    LCD_PORT |= (1 << LCD_RS); // RS = 1
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Display string on LCD
void LCD_string(const char *str) {
    while (*str) {
        LCD_data(*str++);
    }
}

// ADC Initialization
void ADC_init(void) {
    ADMUX = (1 << REFS0); // AVCC with external capacitor at AREF
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, interrupt, prescaler 128
    ADCSRA |= (1 << ADSC); // Start first conversion
}

// PWM Initialization (Timer2, Fast PWM for Fan Control via Transistor)

void PWM_init(void) {
    FAN_PWM_DDR |= (1 << FAN_PWM_PIN); // Set PD7 (OC2) as output
    TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21); // Fast PWM, non-inverted, prescaler 8
    OCR2 = 0; // Initial duty cycle 0% (fan off)
}

// Set fan speed (0-255) via PWM to control transistor
void set_fan_speed(uint8_t duty_cycle) {
    OCR2 = duty_cycle; // Set PWM duty cycle (0 = off, 127 = 50%, 255 = 100%)
}

// Buzzer Initialization
void Buzzer_init(void) {
    BUZZER_DDR |= (1 << BUZZER_PIN);
    Buzzer_off();
}

// Turn buzzer on
void Buzzer_on(void) {
    BUZZER_PORT |= (1 << BUZZER_PIN);
}

// Turn buzzer off
void Buzzer_off(void) {
    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

// LED Initialization
void LED_init(void) {
    LED_DDR |= (1 << LED_PIN);
    LED_off();
}

// Turn LED on
void LED_on(void) {
    LED_PORT |= (1 << LED_PIN);
}

// Turn LED off
void LED_off(void) {
    LED_PORT &= ~(1 << LED_PIN);
}

// Button Initialization (Manual Button only)
void Button_init(void) {
    BUTTON_DDR &= ~(1 << BUTTON_MANUAL); // Input
    PORTB |= (1 << BUTTON_MANUAL); // Enable pull-up for manual button
}

// Display temperature on LCD
void display_temperature(float temp) {
    LCD_command(0x80); // Move to first line
    LCD_string("Temp: ");
    int temp_int = (int)(temp * 10);
    int integer_part = temp_int / 10;
    int decimal_part = temp_int % 10;
    if (integer_part > 99) LCD_data(integer_part / 100 + '0');
    if (integer_part > 9) LCD_data((integer_part / 10) % 10 + '0');
    LCD_data(integer_part % 10 + '0');
    LCD_data('.');
    LCD_data(decimal_part + '0');
    LCD_string(" C");
}

 ***************************************************************************************************/


/*

#define F_CPU 16000000UL  // ?????? 16 ????????
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ????? ?????? LCD
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define LCD_RS PC4
#define LCD_RW PC5
#define LCD_EN PC6
#define LCD_D4 PC0
#define LCD_D5 PC1
#define LCD_D6 PC2
#define LCD_D7 PC3

// ????? ???????? ??????
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PB0      // ???? ??? LED
#define BUTTON_PORT PORTB
#define BUTTON_DDR DDRB
#define BUTTON_PIN PINB
#define BUTTON_MANUAL PB1   // ???? ???? ??????
#define BUZZER_PORT PORTB
#define BUZZER_DDR DDRB
#define BUZZER_PIN PB2   // ???? ??????
#define FAN_PWM_PORT PORTD
#define FAN_PWM_DDR DDRD
#define FAN_PWM_PIN PD7  // ???? ??????? (OC2 ?? PWM)
#define BUTTON1 PD2      // ?? ??? ??????? (INT0)
#define BUTTON2 PD3      // ?? ????? ??????? (INT1)

// Temperature Thresholds
volatile uint8_t threshold_low = 25;  // Default low threshold (25°C)
volatile uint8_t threshold_high = 30; // Default high threshold (30°C)
volatile uint8_t threshold_critical = 35; // Default critical threshold (35°C)

// Function Prototypes
void LCD_init(void);
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_string(const char *str);
void ADC_init(void);
void PWM_init(void);
void set_fan_speed(uint8_t duty_cycle);
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
void LED_init(void);
void LED_on(void);
void LED_off(void);
void Button_init(void);
void display_temperature(float temp);
void display_threshold(uint8_t mode);

// Global Variables
volatile uint16_t adc_value = 0;
volatile float temperature = 0.0;
volatile uint8_t setting_mode = 0; // 0: Normal, 1: Set low, 2: Set high, 3: Set critical
volatile uint8_t manual_fan = 0;   // 0: Auto, 1: Manual (on/off)

// ADC Interrupt Service Routine
ISR(ADC_vect) {
    adc_value = ADC; // Read ADC value
    float voltage = (adc_value * 5.0) / 1023.0; // ????? ??? ??? (???? 5V)
    temperature = voltage * 100.0; // LM35: 10mV/°C
    
    // Fan Control Logic (Auto mode)
    if (!manual_fan) {
        if (temperature < threshold_low) {
            set_fan_speed(0); // Fan off
        } else if (temperature >= threshold_low && temperature < threshold_high) {
            set_fan_speed(127); // 50% speed
        } else {
            set_fan_speed(255); // 100% speed
        }
    }
    
    // Buzzer and LED Control
    if (temperature >= threshold_critical) {
        Buzzer_on();
        LED_on();
    } else {
        Buzzer_off();
        LED_off();
    }
    
    // Restart ADC conversion
    ADCSRA |= (1 << ADSC);
}

// INT0 ISR (Button1: Enter/Exit setting mode or confirm)
ISR(INT0_vect) {
    _delay_ms(50); // Debounce
    if (!(PIND & (1 << BUTTON1))) {
        setting_mode = (setting_mode + 1) % 4; // Cycle through modes (0->1->2->3->0)
    }
}

// INT1 ISR (Button2: Increment threshold)
ISR(INT1_vect) {
    _delay_ms(50); // Debounce
    if (!(PIND & (1 << BUTTON2))) {
        if (setting_mode == 1) {
            threshold_low = (threshold_low < 40) ? threshold_low + 1 : threshold_low;
        } else if (setting_mode == 2) {
            threshold_high = (threshold_high < 50) ? threshold_high + 1 : threshold_high;
        } else if (setting_mode == 3) {
            threshold_critical = (threshold_critical < 60) ? threshold_critical + 1 : threshold_critical;
        }
    }
}

int main(void) {
    // Initialize peripherals
    LCD_init();
    ADC_init();
    PWM_init();
    Buzzer_init();
    LED_init();
    Button_init();
    
    // Enable global interrupts
    sei();
    
    // Display startup message
    LCD_command(0x01); // Clear display
    LCD_string("Temp: --.- C");
    
    while (1) {
        // Check manual fan control button (PB1)
        if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) { // Active-low
            _delay_ms(200); // Debounce
            if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) {
                manual_fan = !manual_fan; // Toggle manual mode
                if (manual_fan) {
                    set_fan_speed(255); // Fan on (100%)
                } else {
                    set_fan_speed(0); // Return to auto mode
                }
            }
        }
        
        if (setting_mode == 0) {
            // Normal mode: Display temperature
            display_temperature(temperature);
        } else {
            // Setting mode: Display thresholds
            display_threshold(setting_mode);
        }
        
        _delay_ms(100); // ????? ????
    }
}

// LCD Initialization (4-bit mode)
void LCD_init(void) {
    LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0 (write mode)
    _delay_ms(50);
    LCD_command(0x02); // 4-bit mode
    LCD_command(0x28); // 2 lines, 5x8 font
    LCD_command(0x0C); // Display on, cursor off
    LCD_command(0x06); // Increment cursor
    LCD_command(0x01); // Clear display
    _delay_ms(5);
}

// Send command to LCD
void LCD_command(uint8_t cmd) {
    LCD_PORT &= ~(1 << LCD_RS); // RS = 0
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Send data to LCD
void LCD_data(uint8_t data) {
    LCD_PORT |= (1 << LCD_RS); // RS = 1
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Display string on LCD
void LCD_string(const char *str) {
    while (*str) {
        LCD_data(*str++);
    }
}

// ADC Initialization
void ADC_init(void) {
    ADMUX = (1 << REFS0); // AVCC with external capacitor at AREF
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, interrupt, prescaler 128
    ADCSRA |= (1 << ADSC); // Start first conversion
}

// PWM Initialization (Timer2, Fast PWM for Fan Control via Transistor)

void PWM_init(void) {
    FAN_PWM_DDR |= (1 << FAN_PWM_PIN); // Set PD7 (OC2) as output
    TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21); // Fast PWM, non-inverted, prescaler 8
    OCR2 = 0; // Initial duty cycle 0% (fan off)
}

// Set fan speed (0-255) via PWM to control transistor
void set_fan_speed(uint8_t duty_cycle) {
    OCR2 = duty_cycle; // Set PWM duty cycle (0 = off, 127 = 50%, 255 = 100%)
}

// Buzzer Initialization
void Buzzer_init(void) {
    BUZZER_DDR |= (1 << BUZZER_PIN); // Set PB2 as output
    Buzzer_off();
}

// Turn buzzer on
void Buzzer_on(void) {
    BUZZER_PORT |= (1 << BUZZER_PIN);
}

// Turn buzzer off
void Buzzer_off(void) {
    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

// LED Initialization
void LED_init(void) {
    LED_DDR |= (1 << LED_PIN); // Set PB0 as output
    LED_off();
}

// Turn LED on
void LED_on(void) {
    LED_PORT |= (1 << LED_PIN);
}

// Turn LED off
void LED_off(void) {
    LED_PORT &= ~(1 << LED_PIN);
}

// Button Initialization (External Interrupts + Manual Button)
void Button_init(void) {
    BUTTON_DDR &= ~((1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON_MANUAL)); // Inputs
    PORTD |= (1 << BUTTON1) | (1 << BUTTON2); // Enable pull-ups for INT0, INT1
    PORTB |= (1 << BUTTON_MANUAL); // Enable pull-up for manual button
    GICR |= (1 << INT0) | (1 << INT1); // Enable INT0, INT1
    MCUCR |= (1 << ISC01) | (1 << ISC11); // Falling edge for INT0, INT1
}

// Display temperature on LCD
void display_temperature(float temp) {
    LCD_command(0x80); // Move to first line
    LCD_string("Temp: ");
    int temp_int = (int)(temp * 10);
    int integer_part = temp_int / 10;
    int decimal_part = temp_int % 10;
    if (integer_part > 99) LCD_data(integer_part / 100 + '0');
    if (integer_part > 9) LCD_data((integer_part / 10) % 10 + '0');
    LCD_data(integer_part % 10 + '0');
    LCD_data('.');
    LCD_data(decimal_part + '0');
    LCD_string(" C");
}

// Display threshold on LCD
void display_threshold(uint8_t mode) {
    LCD_command(0x01); // Clear display
    if (mode == 1) {
        LCD_string("Set Low: ");
        LCD_data((threshold_low / 10) + '0');
        LCD_data((threshold_low % 10) + '0');
        LCD_string(" C");
    } else if (mode == 2) {
        LCD_string("Set High: ");
        LCD_data((threshold_high / 10) + '0');
        LCD_data((threshold_high % 10) + '0');
        LCD_string(" C");
    } else if (mode == 3) {
        LCD_string("Set Crit: ");
        LCD_data((threshold_critical / 10) + '0');
        LCD_data((threshold_critical % 10) + '0');
        LCD_string(" C");
    }
}
*/

/*
#define F_CPU 16000000UL  // ?????? 16 ????????
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ????? ?????? LCD ????? ??? ???????
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define LCD_RS PC4
#define LCD_RW PC5
#define LCD_EN PC6
#define LCD_D4 PC0
#define LCD_D5 PC1
#define LCD_D6 PC2
#define LCD_D7 PC3

// ????? ???????? ??????
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PB0      // ???? ??? LED
#define BUTTON_PORT PORTB
#define BUTTON_DDR DDRB
#define BUTTON_PIN PINB
#define BUTTON_MANUAL PB3   // ???? ???? ??????
#define BUZZER_PORT PORTD
#define BUZZER_DDR DDRD
#define BUZZER_PIN PD0   // ???? ??????
#define FAN_PWM_PORT PORTD
#define FAN_PWM_DDR DDRD
#define FAN_PWM_PIN PD7  // ???? ??????? (OC2 ?? PWM)
#define BUTTON_SET PD2   // ?? ??? ??????? (INT0)

// Temperature Thresholds
volatile uint8_t threshold_low = 25;  // Default low threshold (25°C)
volatile uint8_t threshold_high = 30; // Default high threshold (30°C)
volatile uint8_t threshold_critical = 35; // Default critical threshold (35°C)

// Function Prototypes
void LCD_init(void);
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_string(const char *str);
void ADC_init(void);
void PWM_init(void);
void set_fan_speed(uint8_t duty_cycle);
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
void LED_init(void);
void LED_on(void);
void LED_off(void);
void Button_init(void);
void display_temperature(float temp);

// Global Variables
volatile uint16_t adc_value = 0;
volatile float temperature = 0.0;
volatile uint8_t setting_mode = 0; // 0: Normal, 1: Set low, 2: Set high, 3: Set critical
volatile uint8_t manual_fan = 0;   // 0: Auto, 1: Manual (on/off)

// ADC Interrupt Service Routine
ISR(ADC_vect) {
    adc_value = ADC; // Read ADC value
    float voltage = (adc_value * 5.0) / 1023.0; // ????? ??? ??? (???? 5V)
    temperature = voltage * 100.0; // LM35: 10mV/°C
    
    // Fan Control Logic (Auto mode)
    if (!manual_fan) {
        if (temperature < threshold_low) {
            set_fan_speed(0); // Fan off
        } else if (temperature >= threshold_low && temperature < threshold_high) {
            set_fan_speed(127); // 50% speed
        } else {
            set_fan_speed(255); // 100% speed
        }
    }
    
    // Buzzer and LED Control
    if (temperature >= threshold_critical) {
        Buzzer_on();
        LED_on();
    } else {
        Buzzer_off();
        LED_off();
    }
    
    // Restart ADC conversion
    ADCSRA |= (1 << ADSC);
}

// INT0 ISR (Button SET: Cycle through thresholds or increment)
ISR(INT0_vect) {
    _delay_ms(50); // Debounce
    if (!(PIND & (1 << BUTTON_SET))) {
        if (setting_mode == 0) {
            setting_mode = 1; // Enter setting mode (low threshold)
        } else if (setting_mode == 1) {
            threshold_low = (threshold_low < 40) ? threshold_low + 1 : threshold_low; // Increment low
        } else if (setting_mode == 2) {
            threshold_high = (threshold_high < 50) ? threshold_high + 1 : threshold_high; // Increment high
        } else if (setting_mode == 3) {
            threshold_critical = (threshold_critical < 60) ? threshold_critical + 1 : threshold_critical; // Increment critical
            setting_mode = 0; // Exit setting mode after critical
        }
        if (setting_mode < 3 && setting_mode > 0) {
            setting_mode++; // Move to next threshold
        }
    }
}

int main(void) {
    // Initialize peripherals
    LCD_init();
    ADC_init();
    PWM_init();
    Buzzer_init();
    LED_init();
    Button_init();
    
    // Enable global interrupts
    sei();
    
    // Display startup message
    LCD_command(0x01); // Clear display
    LCD_string("Temp: --.- C");
    
    while (1) {
        // Check manual fan control button (PB3)
        if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) { // Active-low
            _delay_ms(200); // Debounce
            if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) {
                manual_fan = !manual_fan; // Toggle manual mode
                if (manual_fan) {
                    set_fan_speed(255); // Fan on (100%)
                } else {
                    set_fan_speed(0); // Return to auto mode
                }
            }
        }
        
        if (setting_mode == 0) {
            // Normal mode: Display temperature
            display_temperature(temperature);
        } else {
            // Setting mode: Display thresholds
            LCD_command(0x01); // Clear display
            if (setting_mode == 1) {
                LCD_string("Set Low: ");
                LCD_data((threshold_low / 10) + '0');
                LCD_data((threshold_low % 10) + '0');
                LCD_string(" C");
            } else if (setting_mode == 2) {
                LCD_string("Set High: ");
                LCD_data((threshold_high / 10) + '0');
                LCD_data((threshold_high % 10) + '0');
                LCD_string(" C");
            } else if (setting_mode == 3) {
                LCD_string("Set Crit: ");
                LCD_data((threshold_critical / 10) + '0');
                LCD_data((threshold_critical % 10) + '0');
                LCD_string(" C");
            }
            _delay_ms(500);
        }
        
        _delay_ms(100); // ????? ????
    }
}

// LCD Initialization (4-bit mode)
void LCD_init(void) {
    LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0 (write mode)
    _delay_ms(50);
    LCD_command(0x02); // 4-bit mode
    LCD_command(0x28); // 2 lines, 5x8 font
    LCD_command(0x0C); // Display on, cursor off
    LCD_command(0x06); // Increment cursor
    LCD_command(0x01); // Clear display
    _delay_ms(5);
}

// Send command to LCD
void LCD_command(uint8_t cmd) {
    LCD_PORT &= ~(1 << LCD_RS); // RS = 0
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Send data to LCD
void LCD_data(uint8_t data) {
    LCD_PORT |= (1 << LCD_RS); // RS = 1
    LCD_PORT &= ~(1 << LCD_RW); // RW = 0
    LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4); // High nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F); // Low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
    _delay_ms(2);
}

// Display string on LCD
void LCD_string(const char *str) {
    while (*str) {
        LCD_data(*str++);
    }
}

// ADC Initialization
void ADC_init(void) {
    ADMUX = (1 << REFS0); // AVCC with external capacitor at AREF
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, interrupt, prescaler 128
    ADCSRA |= (1 << ADSC); // Start first conversion
}

// PWM Initialization (Timer2, Fast PWM for Fan Control via Transistor)

void PWM_init(void) {
    FAN_PWM_DDR |= (1 << FAN_PWM_PIN); // Set PD7 (OC2) as output
    TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21); // Fast PWM, non-inverted, prescaler 8
    OCR2 = 0; // Initial duty cycle 0% (fan off)
}

// Set fan speed (0-255) via PWM to control transistor
void set_fan_speed(uint8_t duty_cycle) {
    OCR2 = duty_cycle; // Set PWM duty cycle (0 = off, 127 = 50%, 255 = 100%)
}

// Buzzer Initialization
void Buzzer_init(void) {
    BUZZER_DDR |= (1 << BUZZER_PIN);
    Buzzer_off();
}

// Turn buzzer on
void Buzzer_on(void) {
    BUZZER_PORT |= (1 << BUZZER_PIN);
}

// Turn buzzer off
void Buzzer_off(void) {
    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

// LED Initialization
void LED_init(void) {
    LED_DDR |= (1 << LED_PIN);
    LED_off();
}

// Turn LED on
void LED_on(void) {
    LED_PORT |= (1 << LED_PIN);
}

// Turn LED off
void LED_off(void) {
    LED_PORT &= ~(1 << LED_PIN);
}

// Button Initialization (Manual Button and SET Button)
void Button_init(void) {
    BUTTON_DDR &= ~(1 << BUTTON_MANUAL); // Input for manual button
    DDRD &= ~(1 << BUTTON_SET); // Input for SET button
    PORTB |= (1 << BUTTON_MANUAL); // Enable pull-up for manual button
    PORTD |= (1 << BUTTON_SET); // Enable pull-up for SET button
    GICR |= (1 << INT0); // Enable INT0
    MCUCR |= (1 << ISC01); // Falling edge for INT0
}

// Display temperature on LCD
void display_temperature(float temp) {
    LCD_command(0x80); // Move to first line
    LCD_string("Temp: ");
    int temp_int = (int)(temp * 10);
    int integer_part = temp_int / 10;
    int decimal_part = temp_int % 10;
    if (integer_part > 99) LCD_data(integer_part / 100 + '0');
    if (integer_part > 9) LCD_data((integer_part / 10) % 10 + '0');
    LCD_data(integer_part % 10 + '0');
    LCD_data('.');
    LCD_data(decimal_part + '0');
    LCD_string(" C");
}
*/








// Define the CPU frequency as 16 MHz for delay calculations
#define F_CPU 16000000UL  // ?????? 16 ????????

// Include necessary AVR libraries for I/O, interrupts, and delays
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Define LCD pins based on the circuit configuration
#define LCD_PORT PORTC      // LCD data and control pins connected to PORTC
#define LCD_DDR DDRC        // Data direction register for PORTC (LCD)
#define LCD_RS PC4          // Register Select pin for LCD (command/data)
#define LCD_RW PC5          // Read/Write pin for LCD
#define LCD_EN PC6          // Enable pin for LCD
#define LCD_D4 PC0          // Data pin D4 for 4-bit LCD mode
#define LCD_D5 PC1          // Data pin D5 for 4-bit LCD mode
#define LCD_D6 PC2          // Data pin D6 for 4-bit LCD mode
#define LCD_D7 PC3          // Data pin D7 for 4-bit LCD mode

// Define other peripheral pins
#define LED_PORT PORTB      // LED connected to PORTB
#define LED_DDR DDRB        // Data direction register for PORTB (LED)
#define LED_PIN PB0         // LED pin on PB0
#define BUTTON_PORT PORTB    // Button connected to PORTB
#define BUTTON_DDR DDRB     // Data direction register for PORTB (button)
#define BUTTON_PIN PINB     // Input register for reading button state
#define BUTTON_MANUAL PB3   // Manual fan control button on PB3
#define BUZZER_PORT PORTD   // Buzzer connected to PORTD
#define BUZZER_DDR DDRD     // Data direction register for PORTD (buzzer)
#define BUZZER_PIN PD0      // Buzzer pin on PD0
#define FAN_PWM_PORT PORTD  // Fan PWM control connected to PORTD
#define FAN_PWM_DDR DDRD    // Data direction register for PORTD (fan)
#define FAN_PWM_PIN PD7     // Fan PWM pin on PD7 (Timer2 output)
#define BUTTON_SET PD2      // Threshold setting button on PD2 (INT0)

// Define temperature thresholds as volatile (used in ISR)
volatile uint8_t threshold_low = 25;      // Low threshold: 25°C (fan off)
volatile uint8_t threshold_high = 30;     // High threshold: 30°C (fan at 50%)
volatile uint8_t threshold_critical = 35; // Critical threshold: 35°C (buzzer/LED on)

// Function prototypes for modularity
void LCD_init(void);                      // Initialize LCD in 4-bit mode
void LCD_command(uint8_t cmd);            // Send command to LCD
void LCD_data(uint8_t data);              // Send data (character) to LCD
void LCD_string(const char *str);         // Display string on LCD
void ADC_init(void);                      // Initialize ADC for temperature sensor
void PWM_init(void);                      // Initialize PWM for fan control
void set_fan_speed(uint8_t duty_cycle);   // Set fan speed via PWM
void Buzzer_init(void);                   // Initialize buzzer
void Buzzer_on(void);                     // Turn buzzer on
void Buzzer_off(void);                    // Turn buzzer off
void LED_init(void);                      // Initialize LED
void LED_on(void);                        // Turn LED on
void LED_off(void);                       // Turn LED off
void Button_init(void);                   // Initialize buttons
void display_temperature(float temp);     // Display temperature on LCD

// Global variables (volatile for ISR access)
volatile uint16_t adc_value = 0;          // Store ADC reading
volatile float temperature = 0.0;         // Store calculated temperature
volatile uint8_t setting_mode = 0;        // Mode: 0=normal, 1=set low, 2=set high, 3=set critical
volatile uint8_t manual_fan = 0;          // Fan mode: 0=auto, 1=manual

// ADC Interrupt Service Routine (triggered on ADC conversion complete)
ISR(ADC_vect) {
	adc_value = ADC;                      // Read 10-bit ADC value
	float voltage = (adc_value * 5.0) / 1023.0; // Convert to voltage (5V reference)
	temperature = voltage * 100.0;        // LM35 sensor: 10mV/°C -> temperature in °C
	
	// Fan control logic in auto mode
	if (!manual_fan) {
		if (temperature < threshold_low) {
			set_fan_speed(0);             // Fan off below low threshold
			} else if (temperature >= threshold_low && temperature < threshold_high) {
			set_fan_speed(127);           // Fan at 50% speed between low and high
			} else {
			set_fan_speed(255);           // Fan at 100% speed above high threshold
		}
	}
	
	// Buzzer and LED control for critical temperature
	if (temperature >= threshold_critical) {
		Buzzer_on();                     // Activate buzzer
		LED_on();                        // Activate LED
		} else {
		Buzzer_off();                    // Deactivate buzzer
		LED_off();                       // Deactivate LED
	}
	
	ADCSRA |= (1 << ADSC);               // Start next ADC conversion
}

// INT0 ISR (triggered by SET button on PD2)
ISR(INT0_vect) {
	_delay_ms(50);                       // Debounce delay
	if (!(PIND & (1 << BUTTON_SET))) {   // Check if SET button is still pressed (active-low)
		if (setting_mode == 0) {
			setting_mode = 1;            // Enter setting mode (low threshold)
			} else if (setting_mode == 1) {
			threshold_low = (threshold_low < 40) ? threshold_low + 1 : threshold_low; // Increment low threshold (max 40°C)
			} else if (setting_mode == 2) {
			threshold_high = (threshold_high < 50) ? threshold_high + 1 : threshold_high; // Increment high threshold (max 50°C)
			} else if (setting_mode == 3) {
			threshold_critical = (threshold_critical < 60) ? threshold_critical + 1 : threshold_critical; // Increment critical threshold (max 60°C)
			setting_mode = 0;            // Exit setting mode
		}
		if (setting_mode < 3 && setting_mode > 0) {
			setting_mode++;              // Move to next threshold
		}
	}
}

// Main program
int main(void) {
	// Initialize all peripherals
	LCD_init();                          // Set up LCD
	ADC_init();                          // Set up ADC
	PWM_init();                          // Set up PWM for fan
	Buzzer_init();                       // Set up buzzer
	LED_init();                          // Set up LED
	Button_init();                       // Set up buttons
	
	sei();                               // Enable global interrupts
	
	LCD_command(0x01);                   // Clear LCD display
	LCD_string("Temp: --.- C");          // Display initial message
	
	while (1) {
		// Check manual fan control button (PB3)
		if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) { // Button pressed (active-low)
			_delay_ms(200);              // Debounce delay
			if (!(BUTTON_PIN & (1 << BUTTON_MANUAL))) {
				manual_fan = !manual_fan; // Toggle between auto and manual mode
				if (manual_fan) {
					set_fan_speed(255);   // Manual mode: fan at 100%
					} else {
					set_fan_speed(0);     // Auto mode: fan off (will be controlled by ADC)
				}
			}
		}
		
		if (setting_mode == 0) {
			// Normal mode: show temperature
			display_temperature(temperature);
			} else {
			// Setting mode: display thresholds
			LCD_command(0x01);           // Clear display
			if (setting_mode == 1) {
				LCD_string("Set Low: "); // Show low threshold
				LCD_data((threshold_low / 10) + '0'); // Tens digit
				LCD_data((threshold_low % 10) + '0'); // Units digit
				LCD_string(" C");        // Unit
				} else if (setting_mode == 2) {
				LCD_string("Set High: "); // Show high threshold
				LCD_data((threshold_high / 10) + '0');
				LCD_data((threshold_high % 10) + '0');
				LCD_string(" C");
				} else if (setting_mode == 3) {
				LCD_string("Set Crit: "); // Show critical threshold
				LCD_data((threshold_critical / 10) + '0');
				LCD_data((threshold_critical % 10) + '0');
				LCD_string(" C");
			}
			_delay_ms(500);              // Delay for display stability
		}
		
		_delay_ms(100);                  // Loop delay for responsiveness
	}
}

// Initialize LCD in 4-bit mode
void LCD_init(void) {
	LCD_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7); // Set LCD pins as outputs
	LCD_PORT &= ~(1 << LCD_RW);      // RW = 0 (write mode)
	_delay_ms(50);                   // Wait for LCD to power up
	LCD_command(0x02);               // Set 4-bit mode
	LCD_command(0x28);               // 2 lines, 5x8 font
	LCD_command(0x0C);               // Display on, cursor off
	LCD_command(0x06);               // Auto-increment cursor
	LCD_command(0x01);               // Clear display
	_delay_ms(5);                    // Delay after clear
}

// Send command to LCD
void LCD_command(uint8_t cmd) {
	LCD_PORT &= ~(1 << LCD_RS);      // RS = 0 for command
	LCD_PORT &= ~(1 << LCD_RW);      // RW = 0 for write
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd >> 4); // Send high nibble
	LCD_PORT |= (1 << LCD_EN);       // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	LCD_PORT = (LCD_PORT & 0xF0) | (cmd & 0x0F); // Send low nibble
	LCD_PORT |= (1 << LCD_EN);       // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);                    // Delay for command execution
}

// Send data to LCD
void LCD_data(uint8_t data) {
	LCD_PORT |= (1 << LCD_RS);       // RS = 1 for data
	LCD_PORT &= ~(1 << LCD_RW);      // RW = 0 for write
	LCD_PORT = (LCD_PORT & 0xF0) | (data >> 4); // Send high nibble
	LCD_PORT |= (1 << LCD_EN);       // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(200);
	LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F); // Send low nibble
	LCD_PORT |= (1 << LCD_EN);       // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);                    // Delay for data write
}

// Display string on LCD
void LCD_string(const char *str) {
	while (*str) {                   // Loop until null terminator
		LCD_data(*str++);            // Send each character
	}
}

// Initialize ADC for temperature sensor
void ADC_init(void) {
	ADMUX = (1 << REFS0);            // Use AVCC as reference (5V)
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, interrupts, prescaler 128
	ADCSRA |= (1 << ADSC);           // Start first conversion
}

// Initialize PWM for fan control (Timer2, Fast PWM)
void PWM_init(void) {
	FAN_PWM_DDR |= (1 << FAN_PWM_PIN); // Set PD7 as output
	TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21); // Fast PWM, non-inverted, prescaler 8
	OCR2 = 0;                        // Initial duty cycle 0% (fan off)
}

// Set fan speed via PWM duty cycle
void set_fan_speed(uint8_t duty_cycle) {
	OCR2 = duty_cycle;               // Set PWM duty cycle (0=off, 255=100%)
}

// Initialize buzzer
void Buzzer_init(void) {
	BUZZER_DDR |= (1 << BUZZER_PIN); // Set PD0 as output
	Buzzer_off();                    // Ensure buzzer is off initially
}

// Turn buzzer on
void Buzzer_on(void) {
	BUZZER_PORT |= (1 << BUZZER_PIN); // Set PD0 high
}

// Turn buzzer off
void Buzzer_off(void) {
	BUZZER_PORT &= ~(1 << BUZZER_PIN); // Set PD0 low
}

// Initialize LED
void LED_init(void) {
	LED_DDR |= (1 << LED_PIN);       // Set PB0 as output
	LED_off();                       // Ensure LED is off initially
}

// Turn LED on
void LED_on(void) {
	LED_PORT |= (1 << LED_PIN);      // Set PB0 high
}

// Turn LED off
void LED_off(void) {
	LED_PORT &= ~(1 << LED_PIN);     // Set PB0 low
}

// Initialize buttons
void Button_init(void) {
	BUTTON_DDR &= ~(1 << BUTTON_MANUAL); // PB3 as input
	DDRD &= ~(1 << BUTTON_SET);      // PD2 as input
	PORTB |= (1 << BUTTON_MANUAL);   // Enable pull-up for PB3
	PORTD |= (1 << BUTTON_SET);      // Enable pull-up for PD2
	GICR |= (1 << INT0);             // Enable INT0 interrupt
	MCUCR |= (1 << ISC01);           // Trigger INT0 on falling edge
}

// Display temperature on LCD
void display_temperature(float temp) {
	LCD_command(0x80);               // Move cursor to first line
	LCD_string("Temp: ");            // Display label
	int temp_int = (int)(temp * 10); // Convert to integer (e.g., 25.3 -> 253)
	int integer_part = temp_int / 10; // Extract integer part (25)
	int decimal_part = temp_int % 10; // Extract decimal part (3)
	if (integer_part > 99) LCD_data(integer_part / 100 + '0'); // Hundreds digit
	if (integer_part > 9) LCD_data((integer_part / 10) % 10 + '0'); // Tens digit
	LCD_data(integer_part % 10 + '0'); // Units digit
	LCD_data('.');                   // Decimal point
	LCD_data(decimal_part + '0');    // Decimal digit
	LCD_string(" C");                // Unit
}