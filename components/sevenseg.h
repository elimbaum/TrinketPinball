/* sevenseg.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef sevenseg_h
#define sevenseg_h

#define SR_DDR		DDRD
#define SR_PORT		PORTD
#define DATA_PIN	4
#define CLOCK_PIN	3

#define N_DIGITS 3

const byte numbers[] =
{
	B11111100,
	B01100000,
	B11011010,
	B11110010,
	B01100110,
	B10110110,
	B10111110,
	B11100000,
	B11111110,
	B11110110
};

void init7seg();

void displayNumber(int n);
void pushByteToDisplay(byte c);
void clearDisplay();

#endif