/* servo.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#include "servo.h"
#include <Arduino.h>
#include "timing.h"

/* This servo code work as follows:
 *
 * [1] Set pin high.
 * [2] Wait for offset period (0.8 ms)
 * [3] Wait for variable period (0 - 1.4 ms)
 * [4] Set pin low.
 * [5] Wait 20ms and repeat.
 */

static int count = 0;

byte upPos = UP_POS;
byte downPos = DOWN_POS;

// stores current servo position
byte servoVal = 0;

void initServo()
{
	SERVO_DDR |= _BV(SERVO_PIN);
	SERVO_PORT |= _BV(SERVO_PIN); // turn on pin

	// Turn on compare match B interrupt
	TIMSK2 |= _BV(OCIE2B);

	//Initial OCR2B doesn't really matter
	count = STAT_OFFSET;

	servoVal = downPos;
}

void initServo(byte up, byte down)
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

void setServo(byte pos)
{
	servoVal = pos;
}

ISR(TIMER2_COMPB_vect)
{
	if(count == STAT_OFFSET)
	{
		OCR2B = TCNT2 + servoVal;
		count = STAT_VARIABLE;

	}
	else if (count == STAT_VARIABLE)
	{
		// end pulse
		SERVO_PORT &= ~_BV(SERVO_PIN);
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
