/* servo.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum / Alex Tavares
 */

#include "servo.h"
#include <Arduino.h>
#include "timing.h"

/* This servo code work as follows:
 *
 * [1] Set pin high.
 * [2] Wait for 'offset' period (exactly 0.8 ms).
 * [3] Wait for 'variable' period (0 - 1.36533 ms).
 * [4] Set pin low.
 * [5] Wait for 'anti-variable' period (1.36533 ms - 'variable' period).
 * [6] Wait for the 'fill' period (exactly 0.08533 ms).
 * [7] Wait for 13 full overflow cycles (exactly 17.74933 ms).
 */

static int state = OVERFLOW_GOAL; // Positive state is a count of full overflow cycles waited

byte upPos = UP_POS;
byte downPos = DOWN_POS;

byte servoVal = 0; // Current servo position

void initServo()
{
	// Initialize pin
	SERVO_DDR |= _BV(SERVO_PIN);
	SERVO_PORT |= _BV(SERVO_PIN); // Turns on pin

	// Enable interrupt
	TIMSK2 |= _BV(OCIE2B);

	// Set default position
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
	switch(state)
	{
		case OVERFLOW_GOAL: // Start 'offset' period
			state = STATE_OFFSET;
			SERVO_PORT |= _BV(SERVO_PIN);
			OCR2B = TCNT2 + OFFSET_LENGTH;
			break;

		case STATE_OFFSET: // Start 'variable' period
			state = STATE_VARIABLE;
			OCR2B = TCNT2 + servoVal;
			break;

		case STATE_VARIABLE: // Start 'anti-variable' period
			state = STATE_ANTI_VAR;
			SERVO_PORT &= ~_BV(SERVO_PIN);
			OCR2B = TCNT2 - servoVal;
			break;

		case STATE_ANTI_VAR: // Start 'fill' period
			state = STATE_FILL;
			OCR2B = TCNT2 + FILL_LENGTH;
			break;

		case STATE_FILL: // Start 13-overflow-cycles wait
			state = 1;
			break;

		default:
			state++;
			break;
	}
}
