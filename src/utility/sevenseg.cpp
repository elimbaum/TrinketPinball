/* sevenseg.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum / Alex Tavares
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

	clearDisplay();
}

/* pushByteToDisplay
 *
 * manual control
 * re-implements shiftOut, LSB first, with faster code to prevent blurring.
 *
 */
static void pushByteToDisplay(byte c)
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
		SR_PORT &= ~(_BV(CLOCK_PIN) | _BV(DATA_PIN));
	}
}

/* displayString
 *
 * scrolls an ascii string across the displays
 * unsupported characters will result in a blank character
 * code is blocking; don't use for realtime applications
 *
 */
void displayString(char text[], int delay)
{
	byte byteArray[] = {0, 0, 0};
	int stringSize = sizeof(text);

	for(int i = 0; i < stringSize; i++)
	{
		char currLetter = text[i];
		if(currLetter < 33 | currLetter > 126) // Blank char
		{
			byteArray = byteArray + 0;
		}
		else if(currLetter >- 33 && currLetter < 48)
		{
			byteArray = byteArray + ascii33[i - 33];
		}
		else if(currLetter >= 48 && currLetter < 58)
		{
			byteArray = byteArray + numbers[i - 48];
		}
		else
		{
			byteArray = byteArray + ascii58[i - 58];
		}
		if((i+1 < stringSize) && !(byteArray[sizeOf(byteArray) - 1] & 1) && (text[i + 1] == 46))
		{
			byteArray[sizeof(byteArray) - 1] |= 1;
			i++;
		}
	}
	byteArray += {0, 0, 0};

	for(int i = 0; i < sizeof(byteArray) - 2; i++)
	{
		displayBytes(byteArray[i], byteArray[i + 1], byteArray[i + 2]);
		delay(delay);
	}
}

/* displayNumber
 * shift out bytes to display the given number.
 * displays leading zeros, and if numbers are out of range,
 * displays "bIg" or "neg".
 */
void displayNumber(int n)
{
	int digitsOutput = 0;
	if(n > 999) {
		displayBytes(B00111110, B01100000, B11110110); // Display "bIg"
	}
	else if(n < 0) {
		displayBytes(B11101100, B11011110, B11110110); // Display "neg"
	}
	else{
		while (digitsOutput < N_DIGITS)
		{
			pushByteToDisplay(numbers[n % 10]);
			n /= 10;
			digitsOutput++;
		}
	}
}

/* displayBytes
 * Display three custom bytes on screen */
void displayBytes(byte a, byte b, byte c)
{
	pushByteToDisplay(c);
	pushByteToDisplay(b);
	pushByteToDisplay(a);
}



void clearDisplay()
{
	displayBytes(0, 0, 0);
}
