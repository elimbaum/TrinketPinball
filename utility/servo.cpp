/* servo.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#include "servo.h"

/* This servo code work as follows:
 * 
 * [1] Set pin high.
 * [2] Wait for offset period (0.8 ms)
 * [3] Wait for variable period (0 - 1.4 ms)
 * [4] Set pin low.
 * [5] Wait 20ms and repeat.
 */

#define STAT_OFFSET -2
#define OFFSET_LENGTH 150 // gives 0.8 ms

#define STAT_VARIABLE -1

#define REFRESH_COUNT 15 // gives about 20 ms

volatile int count = 0;

/* These are timing figures, not angles */
int upPos = 0;
int downPos = 127;

// stores current servo position
int servoVal;

void initServo()
{
	SERVO_DDR |= _BV(SERVO_PIN);
	SERVO_PORT |= _BV(SERVO_PIN); // turn on pin

	// Turn on compare match B interrupt
	TIMSK0 |= _BV(OCIE0B);

	OCR0B = TCNT0 + OFFSET_LENGTH;
	count = STAT_OFFSET;

	servoVal = downPos;
}

void initServo(int up, int down)
{
	upPos = up;
	downPos = down;
	initServo();
}

void servoUp()
{
	servoVal = upPos;
}

void servoDown()
{
	servoVal = downPos;
}

/* for testing */
void servoWrite(int pos)
{
	servoVal = pos;
}

ISR(TIMER0_COMPB_vect)
{
	int c = count;
	if(c == STAT_OFFSET)
	{
		OCR0B = TCNT0 + servoVal;
		c = STAT_VARIABLE;
	}
	else if (c == STAT_VARIABLE)
	{
		// end pulse
		SERVO_PORT &= ~_BV(SERVO_PIN);

		OCR0B = 0xFF;
		c = 0; // start refresh wait
	}
	else if(c == REFRESH_COUNT)
	{
		// start pulse
		SERVO_PORT |= _BV(SERVO_PIN);
		
		OCR0B = TCNT0 + OFFSET_LENGTH;
		c = STAT_OFFSET;
	}
	else
	{
		// in refresh wait
		c++;
	}
	count = c;
}