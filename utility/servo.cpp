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

#define REFRESH_COUNT 14 // gives about 20 ms

static int count = 0;

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
	TIMSK2 |= _BV(OCIE2B);

	OCR2B = TCNT2 + OFFSET_LENGTH;
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

ISR(TIMER2_COMPB_vect)
{
	// check OCR0B overflow?

	if(count == STAT_OFFSET)
	{
		OCR2B = TCNT2 + servoVal;
		count = STAT_VARIABLE;
	}
	else if (count == STAT_VARIABLE)
	{
		// end pulse
		SERVO_PORT &= ~_BV(SERVO_PIN);
		
		OCR2B = 0xFF;
		count = 0; // start refresh wait
	}
	else if(count == REFRESH_COUNT)
	{
		// start pulse
		SERVO_PORT |= _BV(SERVO_PIN);

		OCR2B = TCNT2 + OFFSET_LENGTH;
		count = STAT_OFFSET;
	}
	else
	{
		// in refresh wait
		count++;
	}
}
