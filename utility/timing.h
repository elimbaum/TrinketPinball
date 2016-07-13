/* timing.h
 *
 * rewrite for Arduino timing functions to use timer2, beacuse
 * we accidentally hooked things up to timer0.
 *
 * specifically written for Trinket Pro / atmega328.
 *
 * code copied from wiring.c
 * largely the same besides changing timer0 -> timer2
 */

#ifndef timing_h
#define timing_h

#define millis() _millis()
#define micros() _micros()
#define delay(ms) _delay(ms)
#define delayMicroseconds(us) _delayMicroseconds(us)

unsigned long _millis();
unsigned long _micros();
void _delay(unsigned long ms);
void _delayMicroseconds(unsigned int us);
void initTiming();


#endif