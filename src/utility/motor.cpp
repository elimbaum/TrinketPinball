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

// 0 - 100 % speed, limited to some maximum
void setMotorSpeed(int speedPercent)
{
	speedPercent = constrain(speedPercent, 0, 100);
	OCR0A = map(speedPercent, 0, 100, 0, MAX_SPEED);
}

// allows full control of motor PWM
void setMotorSpeedPWM(byte speed)
{
	OCR0A = speed;
}
