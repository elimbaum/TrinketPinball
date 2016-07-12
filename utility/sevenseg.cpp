/* sevenseg.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */


#include "sevenseg.h"

/* === 7-seg Display ===
 *
 * LED Arrangement:
 *     A
 *    F_B [G in middle]
 *    E C
 *     D  dp
 *
 * Linearized byte form is: ABCDEFGdp
 * TODO check dp!
 * Shift registers should be connected with most significant digit first.
 */
void init7seg()
{
	SR_DDR |= _BV(DATA_PIN);
	SR_DDR |= _BV(CLOCK_PIN);
}

/* displayNumber
 * shift out bytes to display the given number.
 * displays leading zeros, and if numbers are too long, only the three least
 * significant digits will be displayed.
 */
void displayNumber(int n)
{
	int digitsOutput = 0;

	while (digitsOutput < N_DIGITS)
	{
		pushByteToDisplay(numbers[n % 10]);
		n /= 10;
		digitsOutput++;
	}
}

//TODO maybe have 3-char function (per digit)

/* pushByteToDisplay
 * manual control. user can create any character.
 *
 * re-implements shiftOut, LSB first, with faster code to prevent blurring.
 *
 */
void pushByteToDisplay(byte c)
{
	for(int i = 0; i < 8; i++)
	{
		if(c & (1 << i))
		{
			SR_PORT |= _BV(DATA_PIN);
		}
		else
		{
			SR_PORT &= ~_BV(DATA_PIN);
		}

		SR_PORT |= _BV(CLOCK_PIN);
		SR_PORT &= ~_BV(CLOCK_PIN);
	}
}

void clearDisplay()
{
	for(int i = 0; i < N_DIGITS; i++)
	{
		pushByteToDisplay(0);
	}
}