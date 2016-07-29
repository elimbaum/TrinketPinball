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

#define DEFAULT_VOL 64
#define MAX_VOL 127

#define PER_MIN_THRESH 5 // Approximately the number of period updates the isr takes

void initSpeaker();
void setSpeaker(byte value);
void setSpeakerVolume(byte volPercent);
void tone(int freq);
void dualTone(int freq1, int freq2);
void speakerOff();

#endif