/* motor.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef motor_h
#define motor_h

#include <Arduino.h>

#define MOTOR_DDR	DDRD
#define MOTOR_PORT	PORTD
#define MOTOR_PIN	6

void initMotor();

void motorSpeed(byte speed);

#endif