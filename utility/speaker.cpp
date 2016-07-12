/* speaker.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "speaker.h"

void initSpeaker()
{
	SPEAKER_DDR |= _BV(SPEAKER_PIN);
	// PWM stuff
}

void speaker(byte value)
{
	OCR2A = value;
}

void tone(int freq)
{

}

void stopTone()
{

}