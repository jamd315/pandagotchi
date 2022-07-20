#ifndef _SEQUENCES_H
#define _SEQUENCES_H

#include <avr/pgmspace.h>
#include "images.h"
#include "AnimationManager.h"
#include "globals.h"  // Face size declarations
// NOTE these are declared backwards for linked list purposes


#pragma region eatAnimation
/*
0 display eat_1
0 sound NOTE_G5 100
600 sound NOTE_D5 100
800 display eat_2
1200 sound NOTE_G4 100
1200 loop 4 times 700 ms per loop
  (1200 + 700i) + 0 display eat3
  (1200 + 700i) + 0 sound NOTE_G3 100
  (1200 + 700i) + 150 sound NOTE_Gb3 100
  (1200 + 700i) + 350 display eat_4
  (1200 + 700i) + 700 continue loop
4000 display satisfied
4000 sound NOTE_G4 50
4075 sound NOTE_G5 100
*/
static const PROGMEM AnimationElement _seq1_elem1 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_TOP,
  .meta = IMAGE_DEFAULT,
  .delay = 0,
  .image = satisfied,
  .next = nullptr
};

static const PROGMEM AnimationElement _seq1_elem2 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_4,
  .next = &_seq1_elem1
};

static const PROGMEM AnimationElement _seq1_elem3 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_3,
  .next = &_seq1_elem2
};

static const PROGMEM AnimationElement _seq1_elem4 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_4,
  .next = &_seq1_elem3
};

static const PROGMEM AnimationElement _seq1_elem5 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_3,
  .next = &_seq1_elem4
};

static const PROGMEM AnimationElement _seq1_elem6 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_4,
  .next = &_seq1_elem5
};

static const PROGMEM AnimationElement _seq1_elem7 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_3,
  .next = &_seq1_elem6
};

static const PROGMEM AnimationElement _seq1_elem8 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_4,
  .next = &_seq1_elem7
};

static const PROGMEM AnimationElement _seq1_elem9 = 
{
  .x = FACE_LEFT,
  .y = FACE_TOP,
  .w = FACE_WIDTH,
  .h = FACE_HEIGHT,
  .meta = IMAGE_DEFAULT,
  .delay = 350,
  .image = eat_3,
  .next = &_seq1_elem8
};

static const PROGMEM AnimationSequence eatAnimation = 
{
  .id = 111,
  .head = &_seq1_elem2
};
#pragma endregion

#pragma region testAnimation

static const PROGMEM AnimationElement _seq2_elem1 = 
{
  .x = 56,
  .y = 40,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 0,
  .image = attention,
  .next = nullptr
};

static const PROGMEM AnimationElement _seq2_elem2 = 
{
  .x = 48,
  .y = 48,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 200,
  .image = attention,
  .next = &_seq2_elem1
};

static const PROGMEM AnimationElement _seq2_elem3 = 
{
  .x = 40,
  .y = 40,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 200,
  .image = attention,
  .next = &_seq2_elem2
};

static const PROGMEM AnimationElement _seq2_elem4 = 
{
  .x = 32,
  .y = 32,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 200,
  .image = attention,
  .next = &_seq2_elem3
};

static const PROGMEM AnimationElement _seq2_elem5 = 
{
  .x = 24,
  .y = 24,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 200,
  .image = attention,
  .next = &_seq2_elem4
};

static const PROGMEM AnimationElement _seq2_elem6 = 
{
  .x = 16,
  .y = 16,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 200,
  .image = attention,
  .next = &_seq2_elem5
};

static const PROGMEM AnimationElement _seq2_elem7 = 
{
  .x = 8,
  .y = 8,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 200,
  .image = attention,
  .next = &_seq2_elem6
};

static const PROGMEM AnimationElement _seq2_elem8 = 
{
  .x = 0,
  .y = 0,
  .w = ICON_WIDTH,
  .h = ICON_HEIGHT,
  .meta = IMAGE_CLEARDISPLAY,
  .delay = 200,
  .image = attention,
  .next = &_seq2_elem7
};


static const PROGMEM AnimationSequence testAnimation = 
{
  .id = 222,
  .head = &_seq2_elem5
};
#pragma endregion

#endif