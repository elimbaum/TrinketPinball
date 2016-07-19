/* speaker.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "speaker.h"

// Current volume of the speaker
int spkrVol = DEFAULT_VOL;

int currentTone = 0;

void initSpeaker()
{
	SPEAKER_DDR |= _BV(SPEAKER_PIN);

	/* timer1
	 * turn on CTC mode & interrupt
	 * turn off clock until user turns it on
	 */
	TCCR1A &= ~ (_BV(WGM10) | _BV(WGM11));
	TCCR1B |= _BV(WGM12);
	TCCR1B &= ~_BV(WGM13);

	TIMSK1 |= _BV(OCIE1A);
	speakerOff();

}

void speaker(byte value)
{
	// turn on hardware PWM (may already be on)
	TCCR0A |= _BV(COM0B1);

	OCR0B = value;
}

// For tone generation.
void speakerVolume(byte volPercent)
{
	volPercent = constrain(volPercent, 0, 100);
	spkrVol = map(volPercent, 0, 100, 0, MAX_VOL);
}

/* Generates a square wave. */
void tone(int freq)
{
	if(currentTone != freq)
	{
		// turn on clock, 64 prescale
		currentTone = freq;
		TCCR1B |= _BV(CS11) | _BV(CS10);
		OCR1A = F_CPU / (2L * 64 * freq);
		TCNT1 = 0;
		OCR0B = spkrVol;
	}
}

void speakerOff()
{
	// turn off timer1 tone clock
	TCCR1B &= ~(_BV(CS11) | _BV(CS10));

	// turn off hardware PWM (disconnect OC0B)
	TCCR0A &= ~ _BV(COM0B1);

	// turn off speaker
	SPEAKER_PORT &= ~_BV(SPEAKER_PIN);
	currentTone = 0;
}

ISR(TIMER1_COMPA_vect)
{
	speaker(spkrVol - OCR0B);
}
