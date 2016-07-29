/* sevenseg.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum / Alex Tavares
 */


#include "sevenseg.h"
#include "timing.h"

/* === 7-seg Display ===
 *
 * LED Arrangement:
 *     A
 *    F_B [G in middle]
 *    E C
 *     D  dp
 *
 * Linearized byte form is: ABCDEFGdp
 * Shift registers should be connected with most significant digit first.
 * The left-most digit is considered digit 0.
 *
 * TODO check dp!
 */


 byte displayBuffer[N_DIGITS];
 bool dpBuffer[N_DIGITS]; // Decimal point override buffer
 bool dpOverride; // Are decimal points overridden?


void init7seg()
{
	SR_DDR |= _BV(DATA_PIN);
	SR_DDR |= _BV(CLOCK_PIN);

	dpOverride = false;
	for(int i = 0; i < N_DIGITS; i++)
	{
		dpBuffer[i] = 0;
	}
	clearDisplay();
}

/* pushByteToDisplay
 *
 * Internal function.
 * Re-implements shiftOut, LSB first, with faster code to prevent ghosting.
 *
 */
static void pushByteToDisplay(byte c)
{
	for(int i = 0; i < 8; i++)
	{
		//Set the data pin to the correct state
		(c & (1 << i)) ? SR_PORT |= _BV(DATA_PIN) : SR_PORT &= ~_BV(DATA_PIN);

		//Cycle the clock pin
		SR_PORT |= _BV(CLOCK_PIN);
		SR_PORT &= ~(_BV(CLOCK_PIN) | _BV(DATA_PIN));
	}
}

/* updateDisplay
 *
 * Internal function.
 * Re-sends the current displayBuffer to the display.
 *
 */
static void updateDisplay()
{
	displayBytes(displayBuffer[0], displayBuffer[1], displayBuffer[2]);
}

/* displayText
 *
 * Scrolls an ascii string of max length 256 across the displays.
 * Unsupported characters will result in a blank character.
 * Inputs too long in length will result in no output.
 * This code is blocking; don't use for realtime applications!
 *
 */
void displayText(char text[], int delayTime)
{
	byte byteArray[3 + 256 + 3] = {0, 0, 0};
	int bAIndex = 3;
	byte tIndex = 0;
	char currLetter = text[tIndex];

	while(currLetter)
	{
		// Map input ascii to segment information byte, save to byteArray
		if(currLetter < 33 | currLetter > 126) // Unsupported character
		{
			byteArray[bAIndex] = 0;
		}
		else
		{
			byteArray[bAIndex] = ascii33[currLetter - 33];
		}
		bAIndex++;
		tIndex++;
		if(!tIndex){ // Input too large, quit while we're ahead
			return;
		}
		currLetter = text[tIndex];

		// Tack periods on to the previous character, if possible
		if((currLetter == '.') && !(byteArray[bAIndex - 1] & 1))
		{
			byteArray[bAIndex - 1] |= 1;
			tIndex++;
			currLetter = text[tIndex];
		}
	}
	// Add those last three buffer bytes to bAIndex
	byteArray[bAIndex] = 0;
	byteArray[bAIndex + 1] = 0;
	byteArray[bAIndex + 2] = 0;
	bAIndex += 3;

	// Now scroll through byteArray and display it
	for(int i = 0; i < bAIndex - 2; i++)
	{
		displayBytes(byteArray[i], byteArray[i + 1], byteArray[i + 2]);
		delay(delayTime);
	}
}

/* displayNumber
 *
 * Shifts out bytes to display the given number.
 * Displays leading zeros, and if numbers are out of range,
 * displays "bIG" or "neg".
 *
 */
void displayNumber(int n)
{
	int digitsOutput = N_DIGITS - 1;
	if(n > 999) {
		displayBytes(B00111110, B01100000, B10111100); // Display "bIG"
	}
	else if(n < 0) {
		displayBytes(B11101100, B11011110, B11110110); // Display "neg"
	}
	else{
		while (digitsOutput >= 0)
		{
			displayBuffer[digitsOutput--] = numbers[n % 10];
			n /= 10;
		}
		updateDisplay();
	}
}

/* displayBytes
 *
 * Displays three custom bytes.
 * Also handles dpOverride and updates displayBuffer.
 *
 */
void displayBytes(byte a, byte b, byte c)
{
	if(dpOverride)
	{
		pushByteToDisplay((c & ~DP_MASK) | !!dpBuffer[2]);
		pushByteToDisplay((b & ~DP_MASK) | !!dpBuffer[1]);
		pushByteToDisplay((a & ~DP_MASK) | !!dpBuffer[0]);
	}
	else
	{
		pushByteToDisplay(c);
		pushByteToDisplay(b);
		pushByteToDisplay(a);
	}
	displayBuffer[0] = a;
	displayBuffer[1] = b;
	displayBuffer[2] = c;
}

/* setDisplayByte
 *
 * Sets a specified digit on the display to a custom byte.
 * Invalid positions do nothing.
 *
 */
 void setDisplayByte(byte a, int pos)
 {
 	if(pos < 0 | pos >= N_DIGITS)
 	{
 		return;
 	}
 	else
 	{
 		displayBuffer[pos] = a;
 		updateDisplay();
 	}
 }

/* getDisplayByte
 *
 * Returns the byte currently displayed at digit 'pos'.
 * Invalid positions return 0.
 *
 */
byte getDisplayByte(int pos)
{
	return (pos < 0 | pos >= N_DIGITS) ? 0 : displayBuffer[pos];
}

/* clearDisplay
 *
 * Clears all three digits of the display.
 *
 */
void clearDisplay()
{
	displayBytes(0, 0, 0);
}

/* enableDPOverride
 *
 * Enables decimal point override.
 * Future display updates will ignore the dp bit, instead using dpBuffer.
 *
 */
void enableDPOverride()
{
	dpOverride = true;
	updateDisplay();
}

/* disableDPOverride
 *
 * Disables decimal point override.
 * Future display updates will treat the dp bit normally, ignoring dpBuffer.
 *
 */
void disableDPOverride()
{
	dpOverride = false;
	updateDisplay();
}

/* setDisplayDP
 *
 * Sets a single bit for dpBuffer.
 * Invalid positions do nothing.
 * NOTE: This does not change display functionality unless decimal point override is enabled.
 *
 */
void setDisplayDP(bool dp, int pos)
{
	if(pos < 0 | pos >= N_DIGITS)
	{
		return;
	}
	else
	{
		dpBuffer[pos] = dp;
		if(dpOverride)
		{
			updateDisplay();
		}
	}
}