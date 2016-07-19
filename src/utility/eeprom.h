/* eeprom.h
 *
 * Library for Eli Whitney Arduino camp 2016
 * Eli Baum
 */

#ifndef eeprom_h
#define eeprom_h

#include <Arduino.h>
#include <EEPROM.h>

#define HIGHSCORE_ADDR 1000
#define GAMECOUNT_ADDR 1010

void clearHighScore();
void updateHighScore(int score);
int  readHighScore();

void clearGameCount();
int  readGameCount();
void updateGameCount();

#endif