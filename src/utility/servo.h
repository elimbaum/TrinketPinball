/* servo.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum / Alex Tavares
 */

#ifndef servo_h
#define servo_h

#include <Arduino.h>

#define SERVO_DDR DDRB
#define SERVO_PORT PORTB
#define SERVO_PIN 0

#define STATE_OFFSET -1
#define STATE_VARIABLE -2
#define STATE_ANTI_VAR -3
#define STATE_FILL -4

#define OFFSET_LENGTH 150 // Gives 0.8 ms
#define FILL_LENGTH 14 // Gives 0.08533 ms

#define OVERFLOW_GOAL 13 // Takes 17.74933 ms to fulfill

/* Default positions
 * These are timing figures, not angles */
#define UP_POS 100 // 1.33334 ms pulse
#define DOWN_POS 200 // 1.86667 ms pulse

void initServo();
void initServo(int up, int down);

void servoUp();
void servoDown();

void setServo(byte pos);


#endif
