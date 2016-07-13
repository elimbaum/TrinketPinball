/* speaker.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "speaker.h"

void initSpeaker()
{
	SPEAKER_DDR |= _BV(SPEAKER_PIN);

	// hardware PWM
	TCCR0B |= _BV(COM0B1);
}

void speaker(byte value)
{
	OCR0B = value;
}

void tone(int freq)
{

}

void stopTone()
{

}