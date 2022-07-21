// Autogenerated.  Takes 246 bytes of flash.
// NOTE these are declared backwards for linked list purposes

#include <avr/pgmspace.h>
#include "sequences.h"
#include "Animator.h"
#include "images.h"
#include "globals.h"  // Face size declarations

#pragma region eatAnimation
static const PROGMEM AnimationElement _eatAnimation_frame_5_id2677902628560 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 500,
 .image = satisfied,
 .next = nullptr
};

static const PROGMEM AnimationElement _eatAnimation_frame_4_id2677902629376 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_4,
 .next = &_eatAnimation_frame_5_id2677902628560
};

static const PROGMEM AnimationElement _eatAnimation_frame_3_id2677902628896 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_3,
 .next = &_eatAnimation_frame_4_id2677902629376
};

static const PROGMEM AnimationElement _eatAnimation_frame_4_id2677902629184 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_4,
 .next = &_eatAnimation_frame_3_id2677902628896
};

static const PROGMEM AnimationElement _eatAnimation_frame_3_id2677902627456 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_3,
 .next = &_eatAnimation_frame_4_id2677902629184
};

static const PROGMEM AnimationElement _eatAnimation_frame_4_id2677902628992 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_4,
 .next = &_eatAnimation_frame_3_id2677902627456
};

static const PROGMEM AnimationElement _eatAnimation_frame_3_id2677902628512 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_3,
 .next = &_eatAnimation_frame_4_id2677902628992
};

static const PROGMEM AnimationElement _eatAnimation_frame_4_id2677902628800 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_4,
 .next = &_eatAnimation_frame_3_id2677902628512
};

static const PROGMEM AnimationElement _eatAnimation_frame_3_id2677902627312 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 350,
 .image = eat_3,
 .next = &_eatAnimation_frame_4_id2677902628800
};

static const PROGMEM AnimationElement _eatAnimation_frame_2_id2677902628608 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 400,
 .image = eat_2,
 .next = &_eatAnimation_frame_3_id2677902627312
};

static const PROGMEM AnimationElement _eatAnimation_frame_1_id2677902627120 = 
{
 .x = FACE_LEFT,
 .y = FACE_TOP,
 .w = FACE_WIDTH,
 .h = FACE_HEIGHT,
 .meta = IMAGE_DEFAULT,
 .delay = 800,
 .image = eat_1,
 .next = &_eatAnimation_frame_2_id2677902628608
};

const PROGMEM AnimationSequence eatAnimation = 
{
 .id = 0,
 .head = &_eatAnimation_frame_1_id2677902627120
};
#pragma endregion eatAnimation

#pragma region testAnimation
static const PROGMEM AnimationElement _testAnimation_frame_13_id2677902630768 = 
{
 .x = 96,
 .y = 0,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = nullptr
};

static const PROGMEM AnimationElement _testAnimation_frame_12_id2677902630432 = 
{
 .x = 88,
 .y = 8,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_13_id2677902630768
};

static const PROGMEM AnimationElement _testAnimation_frame_11_id2677902630240 = 
{
 .x = 80,
 .y = 16,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_12_id2677902630432
};

static const PROGMEM AnimationElement _testAnimation_frame_10_id2677902630576 = 
{
 .x = 72,
 .y = 24,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_11_id2677902630240
};

static const PROGMEM AnimationElement _testAnimation_frame_9_id2677902627360 = 
{
 .x = 64,
 .y = 32,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_10_id2677902630576
};

static const PROGMEM AnimationElement _testAnimation_frame_8_id2677902629712 = 
{
 .x = 56,
 .y = 40,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_9_id2677902627360
};

static const PROGMEM AnimationElement _testAnimation_frame_7_id2677902630336 = 
{
 .x = 48,
 .y = 48,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_8_id2677902629712
};

static const PROGMEM AnimationElement _testAnimation_frame_6_id2677902629328 = 
{
 .x = 40,
 .y = 40,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_7_id2677902630336
};

static const PROGMEM AnimationElement _testAnimation_frame_5_id2677902630144 = 
{
 .x = 32,
 .y = 32,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_6_id2677902629328
};

static const PROGMEM AnimationElement _testAnimation_frame_4_id2677902629664 = 
{
 .x = 24,
 .y = 24,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_5_id2677902630144
};

static const PROGMEM AnimationElement _testAnimation_frame_3_id2677902629952 = 
{
 .x = 16,
 .y = 16,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_4_id2677902629664
};

static const PROGMEM AnimationElement _testAnimation_frame_2_id2677902628944 = 
{
 .x = 8,
 .y = 8,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_3_id2677902629952
};

static const PROGMEM AnimationElement _testAnimation_frame_1_id2677902629760 = 
{
 .x = 0,
 .y = 0,
 .w = ICON_WIDTH,
 .h = ICON_HEIGHT,
 .meta = IMAGE_CLEARDISPLAY,
 .delay = 200,
 .image = attention,
 .next = &_testAnimation_frame_2_id2677902628944
};

const PROGMEM AnimationSequence testAnimation = 
{
 .id = 1,
 .head = &_testAnimation_frame_1_id2677902629760
};
#pragma endregion testAnimation

