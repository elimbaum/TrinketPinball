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

#define STAT_OFFSET -2
#define OFFSET_LENGTH 150 // gives 0.8 ms

#define STAT_VARIABLE -1

#define REFRESH_COUNT 14 // gives about 20 ms
 
void initServo();
void initServo(int up, int down);

void servoUp();
void servoDown();

void servoWrite(int pos);


#endif