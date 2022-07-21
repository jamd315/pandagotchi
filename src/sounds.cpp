// Autogenerated.  Takes 107 bytes of flash

#include <avr/pgmspace.h>
#include "sounds.h"
#include "notes.h"
#include "globals.h"
#include "Animator.h"

#pragma region testSound
static const PROGMEM SoundElement _testSound_note_13_id1470689794608 = 
{
 .frequency = NOTE_A4,
 .duration = 200,
 .delay = 0,
 .next = nullptr
};

static const PROGMEM SoundElement _testSound_note_12_id1470689795040 = 
{
 .frequency = NOTE_G4,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_13_id1470689794608
};

static const PROGMEM SoundElement _testSound_note_11_id1470689793120 = 
{
 .frequency = NOTE_F4,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_12_id1470689795040
};

static const PROGMEM SoundElement _testSound_note_10_id1470689795904 = 
{
 .frequency = NOTE_E4,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_11_id1470689793120
};

static const PROGMEM SoundElement _testSound_note_9_id1470689795184 = 
{
 .frequency = NOTE_D4,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_10_id1470689795904
};

static const PROGMEM SoundElement _testSound_note_8_id1470689795952 = 
{
 .frequency = NOTE_C4,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_9_id1470689795184
};

static const PROGMEM SoundElement _testSound_note_7_id1470689794128 = 
{
 .frequency = NOTE_B3,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_8_id1470689795952
};

static const PROGMEM SoundElement _testSound_note_6_id1470689795232 = 
{
 .frequency = NOTE_A3,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_7_id1470689794128
};

static const PROGMEM SoundElement _testSound_note_5_id1470689793744 = 
{
 .frequency = NOTE_G3,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_6_id1470689795232
};

static const PROGMEM SoundElement _testSound_note_4_id1470689793984 = 
{
 .frequency = NOTE_F3,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_5_id1470689793744
};

static const PROGMEM SoundElement _testSound_note_3_id1470689795664 = 
{
 .frequency = NOTE_E3,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_4_id1470689793984
};

static const PROGMEM SoundElement _testSound_note_2_id1470689794176 = 
{
 .frequency = NOTE_D3,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_3_id1470689795664
};

static const PROGMEM SoundElement _testSound_note_1_id1470689794656 = 
{
 .frequency = NOTE_C3,
 .duration = 200,
 .delay = 0,
 .next = &_testSound_note_2_id1470689794176
};

const PROGMEM SoundSequence testSound = 
{
 .id = 0,
 .head = &_testSound_note_1_id1470689794656
};
#pragma endregion testSound

