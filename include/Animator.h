#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H
#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>
#include <Adafruit_SSD1306.h>

#define IMAGE_DEFAULT 0  // Default is non-inverted, opaque, doesn't clear display
#define IMAGE_INVERT 1 << 1
#define IMAGE_TRANSPARENT 1 << 2
#define IMAGE_CLEARDISPLAY 1 << 3

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

struct SoundElement
{
    uint16_t frequency;
    uint16_t duration;
    uint16_t delay;
};


class Animator
{
public:
    Animator(Task &animTask, Task &soundTask, Adafruit_SSD1306 &display, uint8_t speakerPin);
    void callbackAnimation();
    void callbackSound();
    void startAnimationSequence(const AnimationSequence &sequence);
    void drawActiveAnimationElement();

protected:
    Task &_animTask;
    Task &_soundTask;
    const AnimationElement *activeAnimationElement;
    Adafruit_SSD1306 &_display;
    uint8_t _speakerPin;
    inline uint8_t getActiveX();
    inline uint8_t getActiveY();
    inline uint8_t getActiveW();
    inline uint8_t getActiveH();
    inline uint8_t getActiveMeta();
    inline uint16_t getActiveDelay();
    inline const uint8_t *getActiveImage();
    inline AnimationElement *getNext();
};

#endif