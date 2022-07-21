// Autogenerated.  Takes 107 bytes of flash

#include <avr/pgmspace.h>
#include "sounds.h"
#include "notes.h"
#include "globals.h"
#include "Animator.h"

#pragma region testSound
static const PROGMEM SoundElement _testSound_note_13_id2677902760496 = 
{
 .frequency = NOTE_A4,
 .duration = 200,
 .delay = 10,
 .next = nullptr
};

static const PROGMEM SoundElement _testSound_note_12_id2677902760928 = 
{
 .frequency = NOTE_G4,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_13_id2677902760496
};

static const PROGMEM SoundElement _testSound_note_11_id2677902759008 = 
{
 .frequency = NOTE_F4,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_12_id2677902760928
};

static const PROGMEM SoundElement _testSound_note_10_id2677902761792 = 
{
 .frequency = NOTE_E4,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_11_id2677902759008
};

static const PROGMEM SoundElement _testSound_note_9_id2677902761072 = 
{
 .frequency = NOTE_D4,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_10_id2677902761792
};

static const PROGMEM SoundElement _testSound_note_8_id2677902761840 = 
{
 .frequency = NOTE_C4,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_9_id2677902761072
};

static const PROGMEM SoundElement _testSound_note_7_id2677902760016 = 
{
 .frequency = NOTE_B3,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_8_id2677902761840
};

static const PROGMEM SoundElement _testSound_note_6_id2677902761120 = 
{
 .frequency = NOTE_A3,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_7_id2677902760016
};

static const PROGMEM SoundElement _testSound_note_5_id2677902759632 = 
{
 .frequency = NOTE_G3,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_6_id2677902761120
};

static const PROGMEM SoundElement _testSound_note_4_id2677902759872 = 
{
 .frequency = NOTE_F3,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_5_id2677902759632
};

static const PROGMEM SoundElement _testSound_note_3_id2677902761552 = 
{
 .frequency = NOTE_E3,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_4_id2677902759872
};

static const PROGMEM SoundElement _testSound_note_2_id2677902760064 = 
{
 .frequency = NOTE_D3,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_3_id2677902761552
};

static const PROGMEM SoundElement _testSound_note_1_id2677902760544 = 
{
 .frequency = NOTE_C3,
 .duration = 200,
 .delay = 10,
 .next = &_testSound_note_2_id2677902760064
};

const PROGMEM SoundSequence testSound = 
{
 .id = 0,
 .head = &_testSound_note_1_id2677902760544
};
#pragma endregion testSound
