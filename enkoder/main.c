#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define delay_ms_1Mhz(x) (_delay_ms(x))   // Delay when prescaller set to 8x
#define delay_ms_16Mhz(x) (_delay_ms(x*16)) // Delay when prescaller set to 1x so we need to burn 8x as many cycles

#define LED (1<<PB5)

int main()
{
	DDRB |= LED;
	
	
	while(1)
	{
		PORTB ^= LED;
		delay_ms_1Mhz(1000);
	}
}