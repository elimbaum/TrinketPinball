/* servo.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef servo_h
#define servo_h

#include <Arduino.h>

#define SERVO_DDR DDRB
#define SERVO_PORT PORTB
#define SERVO_PIN 0
 
void initServo();
void initServo(int up, int down);

void servoUp();
void servoDown();

void servoWrite(int pos);


#endif