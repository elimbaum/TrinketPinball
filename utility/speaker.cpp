/* speaker.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "speaker.h"

void initSpeaker()
{
	SPEAKER_DDR |= _BV(SPEAKER_PIN);

	/* timer1
	 * turn on CTC mode, interrupt
	 * turn off clock until user turns it on
	 */
	TCCR1A &= ~ (_BV(WGM10) | _BV(WGM11));
	TCCR1B |= _BV(WGM12);
	TCCR1B &= ~_BV(WGM13);

	TIMSK1 |= _BV(OCIE1A);
	stopTone();

}

void speaker(byte value)
{
	// turn on hardware PWM
	TCCR0A |= _BV(COM0B1);

	OCR0B = value;
}

/* Generates a square wave. */
void tone(int freq)
{
	// turn on clock, 64 prescale
	TCCR1B |= _BV(CS11) | _BV(CS10);
	OCR1A = F_CPU / (64 * freq);
}

void stopTone()
{
	// turn off clock
	TCCR1B &= ~(_BV(CS11) | _BV(CS10));

	// turn off speaker
	SPEAKER_PORT &= ~_BV(SPEAKER_PIN);
}

ISR(TIMER1_COMPA_vect)
{
	// turn off hardware PWM
	TCCR0A &= ~_BV(COM0B1);

	// turn off speaker
	SPEAKER_PORT &= ~_BV(SPEAKER_PIN);
}