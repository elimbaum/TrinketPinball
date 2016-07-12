/* ewm.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef ewm_h
#define emw_h

#include "Arduino.h"

#include "sevenseg.h"
#include "eeprom.h"
#include "servo.h"

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

/* EEPROM High Score */
#define HIGHSCORE_ADDR 1000

/* Pin definitions */
// LEDs
#define BUMP_0_LED		9
#define BUMP_1_LED		10
#define BUMP_2_LED		11
// Inputs
#define BUMP_0_SENSE	12
#define BUMP_1_SENSE	A0
#define BUMP_2_SENSE	A1
#define FLIP_L_SENSE	A2
#define FLIP_R_SENSE	A3
#define OUT_SENSE		A4
#define	RAMP_SENSE		A5

#define SPEAKER_DDR		DDRD
#define SPEAKER_PORT	PORTD
#define SPEAKER_PIN		5	

#define MOTOR_DDR		DDRD
#define MOTOR_PORT		PORTD
#define MOTOR_PIN		6


/* Function definitions */
void initPinball();

#endif