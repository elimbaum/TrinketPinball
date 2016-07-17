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

/* These are timing figures, not angles */
int upPos = UP_POS;
int downPos = DOWN_POS;

// stores current servo position
int servoVal = 0;

long t_start, t_mid, t_end;
byte c_start, c_mid, c_end;

void initServo()
{
	SERVO_DDR |= _BV(SERVO_PIN);
	SERVO_PORT |= _BV(SERVO_PIN); // turn on pin

	// Turn on compare match B interrupt
	TIMSK2 |= _BV(OCIE2B);

	//Initial OCR2B doesn't really matter
	//OCR2B = TCNT2 + OFFSET_LENGTH;
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

/*void servoPrint()
{
	long _ts = t_start;
	long _tm = t_mid;
	long _te = t_end;

	byte _cs = c_start;
	byte _cm = c_mid;
	byte _ce = c_end;

	if(_te > 0)
	{
		Serial.println("==========");
		Serial.print("ts\t"); Serial.print(_ts);
			Serial.print("\t @ "); Serial.println(_cs);
		Serial.print("tm\t"); Serial.print(_tm);
			Serial.print("\t @ "); Serial.println(_cm);
		Serial.print("te\t"); Serial.print(_te);
			Serial.print("\t @ "); Serial.println(_ce);
		Serial.print("tm - ts: "); Serial.println(_tm - _ts);
		Serial.print("te - tm: "); Serial.println(_te - _tm);
		Serial.print("te - ts: "); Serial.println(_te - _ts);
		Serial.println();
	}

}*/

ISR(TIMER2_COMPB_vect)
{
	//byte t = TCNT2;
	if(count == STAT_OFFSET)
	{
		OCR2B = TCNT2 + servoVal;
		count = STAT_VARIABLE;

		// debug
		/*c_mid = TCNT2;
		t_mid = micros();*/

	}
	else if (count == STAT_VARIABLE)
	{
		// end pulse
		SERVO_PORT &= ~_BV(SERVO_PIN);
		
		count = 0; // start refresh wait

		// debug
		/*c_end = TCNT2;
		t_end = micros();*/
	}
	else if(count == REFRESH_COUNT)
	{
		// start pulse
		SERVO_PORT |= _BV(SERVO_PIN);

		OCR2B = TCNT2 + OFFSET_LENGTH;
		count = STAT_OFFSET;

		/*c_start = TCNT2;
		t_start = micros();
		t_end = -1;*/
	}
	else
	{
		// in refresh wait
		count++;
	}
}
