#ifndef _ANIMATOR_H
#define _ANIMATOR_H
#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>
#include <Adafruit_SSD1306.h>

#define IMAGE_DEFAULT 0  // Default is non-inverted, opaque, doesn't clear display
#define IMAGE_INVERT 1 << 1
#define IMAGE_TRANSPARENT 1 << 2
#define IMAGE_CLEARDISPLAY 1 << 3
#define IMAGE_DRAWONLY 1 << 4

// Comment out to reduce log volume by omitting Animator logs
//#define USE_SERIAL_ANIMATOR

// This is in PROGMEM
typedef struct AnimationElement
{
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t h;
    uint8_t meta;
    uint16_t delay;
    const uint8_t *image;
    const AnimationElement *next;
} AnimationElement;

// This is in PROGMEM
typedef struct AnimationSequence
{
    uint8_t id;  // Just for debugging
    const AnimationElement *head;
} AnimationSequence;

// This is in PROGMEM
typedef struct SoundElement
{
    uint16_t frequency;
    uint16_t duration;
    uint16_t delay;
    const SoundElement *next;
} SoundElement;

// This is in PROGMEM
typedef struct SoundSequence
{
    uint8_t id;  // Just for debugging
    const SoundElement *head;
} SoundSequence;


class Animator
{
public:
    Animator(Task &animTask, Task &soundTask, Adafruit_SSD1306 &display, uint8_t speakerPin);
    void callbackAnimation();
    void callbackSound();
    void startAnimationSequence(const AnimationSequence &sequence, bool invert=false);
    void showFace(const AnimationSequence &face, bool invert=false);
    void startSoundSequence(const SoundSequence &sequence);
    void drawActiveAnimationElement();

    // Hardcoded animations that need some context
    void cleanAnimation(bool invert=false);

protected:
    Task &_animTask;
    Task &_soundTask;
    const AnimationElement *activeAnimationElement;
    const SoundElement *activeSoundElement;
    Adafruit_SSD1306 &_display;
    uint8_t _speakerPin;
    bool _sequenceInvert = false;
    uint8_t xContext;  // Used for hardcoded animations
    inline uint8_t getAnimX();
    inline uint8_t getAnimY();
    inline uint8_t getAnimW();
    inline uint8_t getAnimH();
    inline uint8_t getAnimMeta();
    inline uint16_t getAnimDelay();
    inline const uint8_t *getActiveImage();
    inline AnimationElement *getAnimNext();
    inline uint16_t getSoundFrequency();
    inline uint16_t getSoundDuration();
    inline uint16_t getSoundDelay();
    inline SoundElement *getSoundNext();
};

#endif