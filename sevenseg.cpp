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
	sbi(SR_DDR, DATA_PIN);
	sbi(SR_DDR, CLOCK_PIN);
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
		pushDigitToDisplay(n % 10);
		n /= 10;
		digitsOutput++;
	}
}

/* pushDigitToDisplay
 * a bit more manual control. Does not automatically clear display.
 */
void pushDigitToDisplay(int n)
{
	pushCharToDisplay(numbers[n]);
}

/* pushCharToDisplay
 * maximum manual control. user can create any character.
 *
 * re-implements shiftOut, LSB first, with faster code to prevent blurring.
 *
 */
void pushCharToDisplay(byte c)
{
	for(int i = 0; i < 8; i++)
	{
		if(c & (1 << i))
		{
			sbi(SR_PORT, DATA_PIN);
		}
		else
		{
			cbi(SR_PORT, DATA_PIN);
		}

		sbi(SR_PORT, CLOCK_PIN);
		cbi(SR_PORT, CLOCK_PIN);
	}
}

void clearDisplay()
{
	for(int i = 0; i < N_DIGITS; i++)
	{
		pushCharToDisplay(0);
	}
}