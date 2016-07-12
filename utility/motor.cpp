/* motor.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "motor.h"

void initMotor()
{
	MOTOR_DDR |= _BV(MOTOR_PIN);
 	// set up motor (hardware timer0) PWM
}

 void motorSpeed(byte speed)
 {
 	// something like this prolly
 	OCR0A = speed;
 }