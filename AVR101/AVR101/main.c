#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

ISR(TIMER1_OVF_vect)
{
	PIND |= (1 << PIND2);
}

int main(void)
{
	// LED
	DDRD |= (1 << DDD2);
	// LED on
	PORTD |= (1 << PORTD2);

	// clk/256
	TCCR1B |= (1 << CS12);
	// timer enabled
	TIMSK1 |= (1 << TOIE1);
	
	sei();
	
	// Switch all off exept timer
	PRR = 0b11110111;

	// set sleep mode
	set_sleep_mode(SLEEP_MODE_IDLE);
	
	while (1)
	{
		sleep_mode();
	}
}

