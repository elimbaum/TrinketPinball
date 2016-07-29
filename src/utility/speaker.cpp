/* speaker.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "speaker.h"

int spkrVol = DEFAULT_VOL;
int currentTone = 0;

bool dualToneMode = false;
bool tone1State = false;
bool tone2State = false;
int currentPer1 = 0;
int currentPer2 = 0;
int remainingPer1;
int remainingPer2;

void initSpeaker()
{
	SPEAKER_DDR |= _BV(SPEAKER_PIN);

	// Set up timer1
	// Set to CTC mode & use ORC1A interrupt
	TCCR1A &= ~(_BV(WGM10) | _BV(WGM11));
	TCCR1B |= _BV(WGM12);
	TCCR1B &= ~_BV(WGM13);

	TIMSK1 |= _BV(OCIE1A); // Enable timer1A interrupt

	speakerOff(); // Turn off speaker until user needs it

}

/* setSpeaker
 *
 * Sets the speaker to an analogue value, using
 * ultrasonic PWM.
 *
 */
void setSpeaker(byte value)
{
	TCCR0A |= _BV(COM0B1);	// Verify ultrasonic PWM is enabled
	OCR0B = value;
}

/* setSpeakerVolume
 * 
 * Sets speaker volume as a percent.
 * Volume used by tone generation functions.
 *
 */
void setSpeakerVolume(byte volPercent)
{
	volPercent = constrain(volPercent, 0, 100);
	spkrVol = map(volPercent, 0, 100, 0, MAX_VOL);
}

/* tone
 *
 * Generates a square wave.
 * Also updates dualToneMode.
 *
 */
void tone(int freq)
{
	dualToneMode = false;

	// Check for frequency of 0
	if(!freq)
	{
		speakerOff();
		return;
	}

	if(currentTone != freq)
	{
		currentTone = freq;

		TCCR1B = (TCCR1B & ~_BV(CS12)) | (_BV(CS11) | _BV(CS10));	// Set clock to 1/64 prescale
		OCR1A = F_CPU / (2L * 64 * freq); // Update OCR1A for correct period
		TCNT1 = 0; // Reset counter
		OCR0B = spkrVol;
	}
}

/* Generates a dual square wave */
void dualTone(int freq1, int freq2)
{
	dualToneMode = true;

	TCCR1B = (TCCR1B & ~_BV(CS12)) | (_BV(CS11) | _BV(CS10));	// Set clock to 1/64 prescale

	// Update current periods
	currentPer1 = F_CPU / (2L * 64 * freq1);
	currentPer2 = F_CPU / (2L * 64 * freq2);
	remainingPer1 = currentPer1;
	remainingPer2 = currentPer2;
	if(remainingPer1 < remainingPer2) 
	{
		OCR1A = remainingPer1;
		remainingPer2 -= remainingPer1;
		remainingPer1 = 0;
	}
	else
	{
		OCR1A = remainingPer2;
		remainingPer1 -= remainingPer2;
		remainingPer2 = 0;
	}
	TCNT1 = 0;
	OCR0B = 0;
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
	if(dualToneMode)
	{
		if(remainingPer1 < PER_MIN_THRESH)
		{
			tone1State = !tone1State;
			remainingPer1 = currentPer1;
		}
		if(remainingPer2 < PER_MIN_THRESH)
		{
			tone2State = !tone2State;
			remainingPer2 = currentPer2;
		}

		setSpeaker((spkrVol * !!tone1State) + (spkrVol * !!tone2State));

		if(remainingPer1 < remainingPer2) 
		{
			OCR1A = remainingPer1;
			remainingPer2 -= remainingPer1;
			remainingPer1 = 0;
		}
		else
		{
			OCR1A = remainingPer2;
			remainingPer1 -= remainingPer2;
			remainingPer2 = 0;
		}
	}
	else
	{
		OCR0B ? setSpeaker(0) : setSpeaker(spkrVol); // Toggle speaker state every 
	}
}
