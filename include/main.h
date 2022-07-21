#ifndef _PANDAGOTCHI_MAIN_H
#define _PANDAGOTCHI_MAIN_H

#include "globals.h"

// Function primitives
void error();
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