#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define delay_ms_1Mhz(x) (_delay_ms(x))   // Delay when prescaller set to 8x
#define delay_ms_16Mhz(x) (_delay_ms(x*16)) // Delay when prescaller set to 1x so we need to burn 8x as many cycles

#define CHANNEL_A PD2 // interrupt 0
#define CHANNEL_B PD4 //
#define LED		  PB5

//#define SENSOR PD3
volatile uint8_t pulseCount = 0;
volatile uint8_t dir = 0; // 0 - right, 1 - left


int main()
{
	DDRB = 0x00;
	DDRD = 0x00;
	DDRB |=  (1<<LED);
	DDRD &=~ (1<<CHANNEL_A)|(1<<CHANNEL_B);
	
	EIMSK = 0b00000011;
	
	// ------------------------EICRA-----------------------------
	// BIT 7 ---- 6 ---- 5 ---- 4 ---- 3 ---- 2 ---- 1 ---- 0 ---
	// --- - ---- - ---- - ---- - ---ISC11--ISC10--ISC01--ISC00 -
	// ------------------------------INTEREUPT 1---INTERRUPT 0---
	//EICRA = 0b00000101; // Logical change
	EICRA = 0b00001111; // Rising edge 
	
	sei();
	while(1)
	{
		
	}
}
ISR(INT0_vect)
{
	if(!(PIND & (1<<CHANNEL_B))) {
		PORTB |= (1<<LED);
		dir = 0;
	}else {
		PORTB &=~ (1<<LED);
		dir = 1;
	}
}