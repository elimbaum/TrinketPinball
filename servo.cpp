/* servo.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#include "servo.h"

void initServo()
{
	serv.attach(SERVO_PIN);
}

void servoUp()
{
	serv.write(UP_POS);
}

void servoDown()
{
	serv.write(DOWN_POS);
}