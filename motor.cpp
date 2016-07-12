/* motor.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

 #include "motor.h"

 void initMotor()
 {
 	// set up motor (hardware timer0) PWM
 }

 void motorSpeed(byte speed)
 {
 	// something like this prolly
 	OCCRA = speed;
 }