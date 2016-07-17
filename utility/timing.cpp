/* timing.cpp
 *
 * rewrite for Arduino timing functions to use timer2, beacuse
 * we accidentally hooked things up to timer0.
 *
 * specifically written for Trinket Pro / atmega328.
 *
 * code copied from wiring.c
 * largely the same besides changing timer0 -> timer2
 */

#include "wiring_private.h"
#include "timing.h"

#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)


volatile unsigned long timer2_overflow_count = 0;
volatile unsigned long timer2_millis = 0;
static unsigned char timer2_fract = 0;

ISR(TIMER2_OVF_vect)
{	
	unsigned long m = timer2_millis;
	unsigned char f = timer2_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer2_fract = f;
	timer2_millis = m;
	timer2_overflow_count++;
}

unsigned long _millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG;

	cli();
	m = timer2_millis;
	SREG = oldSREG;

	return m;
}

unsigned long _micros()
{
	unsigned long m;
	uint8_t oldSREG = SREG, t;
	
	cli();
	m = timer2_overflow_count;
	t = TCNT2;

	if ((TIFR2 & _BV(TOV2)) && (t < 255))
		m++;

	SREG = oldSREG;

	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}

void _delay(unsigned long ms)
{
	uint32_t start = micros();

	while (ms > 0) {
		yield();
		while ( ms > 0 && (micros() - start) >= 1000) {
			ms--;
			start += 1000;
		}
	}
}

void _delayMicroseconds(unsigned int us)
{
	// for a 1 microsecond delay, simply return.  the overhead
	// of the function call takes 14 (16) cycles, which is 1.5us
	if (us <= 1) return; //  = 3 cycles, (4 when true)

	// the following loop takes 1/3 of a microsecond (4 cycles)
	// per iteration, so execute it three times for each microsecond of
	// delay requested.
	us = (us << 1) + us; // x3 us, = 5 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 20 (22) cycles above, remove 5, (5*4=20)
	// us is at least 6 so we can substract 5
	us -= 5; //2 cycles

	__asm__ __volatile__ (
		"1: sbiw %0,1" "\n\t" // 2 cycles
		"brne 1b" : "=w" (us) : "0" (us) // 2 cycles
	);
}

void initTiming()
{
	sei();

	// Timer2
	// prescale factor 64
	TCCR2B |= _BV(CS22);
	TCCR2B &= ~ (_BV(CS21) | _BV(CS20));

	// Normal mode
	TCCR2A &= ~(_BV(WGM20) | _BV(WGM21));
	TCCR2B &= ~_BV(WGM22) ;

	// overflow interrupt
	TIMSK2 |= _BV(TOIE2);

	/* Timer0 setup for motor and speaker
	 * timer0 should already be in fast PWM mode
	 * prescale 1 (24kHz overall freq)
	 */
	TCCR0B |= _BV(CS00);
	TCCR0B &= ~ (_BV(CS01) | _BV(CS02));
}


