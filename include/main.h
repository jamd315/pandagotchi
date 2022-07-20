#ifndef _PANDAGOTCHI_MAIN_H
#define _PANDAGOTCHI_MAIN_H

#include "globals.h"

// Function primitives
void error();
#ifndef USE_SOUND
// If not using sound, catch calls to tone() and do nothing
void tone(int pin, int freq) { }
void tone(int pin, int freq, int duration) { }
#endif
void drawMenu();
uint8_t getMenuX(uint8_t index);
uint8_t getMenuY(uint8_t index);
void btnCheck();
void test();
void callbackAnimationWrapper();
void callbackSoundWrapper();
void testAnimator();
#ifdef USE_SERIAL
void showStatus();
#endif

#endif