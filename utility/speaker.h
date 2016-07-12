/* speaker.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef speaker_h
#define speaker_h

#include <Arduino.h>

#define SPEAKER_DDR		DDRD
#define SPEAKER_PORT	PORTD
#define SPEAKER_PIN		5

#define PWM_MAX

void initSpeaker();
void speaker(byte value);
void tone(int freq);
void stopTone();

#endif