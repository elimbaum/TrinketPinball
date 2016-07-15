/* motor.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef motor_h
#define motor_h

#include <Arduino.h>

#define MOTOR_DDR	DDRD
#define MOTOR_PIN	6

#define MAX_SPEED 127

void initMotor();

void motorSpeed(int speedPercent);
void motorSpeedPWM(byte speed);

#endif