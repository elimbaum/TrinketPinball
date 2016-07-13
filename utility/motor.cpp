/* motor.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "motor.h"

void initMotor()
{
	MOTOR_DDR |= _BV(MOTOR_PIN);

 	// hardware PWM
 	TCCR0A |= _BV(COM0A1);
}

void motorSpeed(byte speed)
{
	OCR0A = speed;
}