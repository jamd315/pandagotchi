#ifndef _PANDAGOTCHI_MAIN_H
#define _PANDAGOTCHI_MAIN_H

#include "globals.h"

// Function primitives
void error();
void btnCheck();
void test();
void callbackAnimationWrapper();
void callbackSoundWrapper();
void callbackPandaWrapper();
#ifdef USE_SERIAL
void showStatus();
#endif

#endif