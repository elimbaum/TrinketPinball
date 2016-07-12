/* eeprom.cpp
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#include "eeprom.h"

 /* === High Score === *
 *
 * We use EEPROM to store high scores, by default. More advanced users can
 * use manual EEPROM functions for string and other number storage.
 * 
 */
void writeHighScore(int score)
{
	EEPROM.put(HIGHSCORE_ADDR, score);
}

int readHighScore()
{
	// does this work? pass by reference
	int score;
	return EEPROM.get(HIGHSCORE_ADDR, score);
}

/* === Number of games played === *
 *
 * Just for fun, save the number of games ever played.
 */
void clearGameCount()
{
	EEPROM.put(GAMECOUNT_ADDR, 0);
}

int getGameCount()
{
	int gameCount;
	return EEPROM.get(GAMECOUNT_ADDR, gameCount);
}

void updateGameCount()
{
	EEPROM.put(GAMECOUNT_ADDR, getGameCount() + 1);
}