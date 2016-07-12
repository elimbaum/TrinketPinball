/* eeprom.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef eeprom_h
#define eeprom_h

#define HIGHSCORE_ADDR 1000
#define GAMECOUNT_ADDR 1010

void clearHighScore();
void writeHighScore(int score);
int  readHighScore();

void clearGameCount();
int  getGameCount();
void updateGameCount();

#endif