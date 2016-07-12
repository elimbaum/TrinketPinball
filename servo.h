/* servo.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef servo_h
#define servo_h

#include <Servo.h>

#define SERVO_PIN 8
#define UP_POS 0
#define DOWN_POS 90

Servo serv;

void initServo();

void servoUp();
void servoDown();

#endif