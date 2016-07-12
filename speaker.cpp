/* speaker.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#include "speaker.h"

void initSpeaker()
{
	// PWM stuff
}

void speaker(byte value)
{
	OCCR2A = value;
}

void tone(int freq)
{

}

void stopTone()
{
	
}