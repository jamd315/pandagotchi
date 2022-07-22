#ifndef _PANDA_H
#define _PANDA_H

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Animator.h"

// Long time, e.g. time spent on neutral state or between asleep checks
#define DELAY_LONG_LOW 10000
#define DELAY_LONG_HIGH 20000

// Standard wait time before consequences, most actions
#define DELAY_MEDIUM_LOW 5000
#define DELAY_MEDIUM_HIGH 10000

// Actions that need to be remedied quickly
#define DELAY_SHORT_HIGH 5000
#define DELAY_SHORT_LOW 1000

// Configurable
#define SLEEP_TIME 28800000  // 8 hours in ms
// Percents
#define UNDECAY_CHANCE 10
#define HEALTH_GAIN_CHANCE 25
#define MISCHIEVIOUS_CHANCE 10
#define WASTE_TO_SICK_CHANCE 40
#define HUNGRY_TO_SICK_CHANCE 20


typedef enum PandaState
{
    FAKE_NEED_ATTENTION,
    SICK,
    WASTE,
    HUNGRY,
    TIRED,
    ASLEEP,
    BORED,
    HAPPY,
    SATISFIED,
    NEUTRAL
} PandaState;

typedef struct StateWeights
{
    uint8_t FakeNeedAttention;
    uint8_t Sick;
    uint8_t Waste;
    uint8_t Hungry;
    uint8_t Tired;
    uint8_t Bored;
} StateWeights;


class Panda
{
public:
    Panda(Task &pandaStateTask, Adafruit_SSD1306 &display, Animator &animator);
    PandaState getNewRandomState();
    void callback();

    void transitionNewRandomState();
    void transitionNeutralState();
    void transitionSatisfiedState();
    void transitionHappyState();
    void transitionSickState();
    void transitionWasteState();
    void transitionHungryState();
    void transitionTiredState();
    void transitionAsleepState();
    void transitionBoredState();
    void transitionFakeNeedsAttentionState();

    void callbackNeutralState();
    void callbackSatisfiedState();
    void callbackHappyState();
    void callbackSickState();
    void callbackWasteState();
    void callbackHungryState();
    void callbackTiredState();
    void callbackAsleepState();
    void callbackBoredState();
    void callbackFakeNeedsAttentionState();

    void displayNeutralState();
    void displaySatisfiedState();
    void displayHappyState();
    void displaySickState();
    void displayWasteState();
    void displayHungryState();
    void displayTiredState();
    void displayAsleepState();
    void displayBoredState();
    void displayFakeNeedsAttentionState();
    void drawMenu();
    uint8_t getMenuX(uint8_t index);
    uint8_t getMenuY(uint8_t index);

    uint32_t getDelayLong(); // Long time, e.g. time spent on neutral state or between asleep checks
    uint32_t getDelayMedium(); // Standard wait time before consequences, most actions
    uint32_t getDelayShort(); // Actions that need to be remedied quickly
    inline uint8_t clampedModify(uint8_t weight, int16_t difference);

protected:
    PandaState _state;
    StateWeights _weights;
    Task &_pandaStateTask;
    Adafruit_SSD1306 &_display;
    Animator &_animator;
    bool _attentionFlag = false;
    uint32_t _sleepStartTime;
    uint8_t _health = 10;
    bool _lightsOn = true;
    uint8_t _menuIndex = 0;
    // These can be modified with traits, all are percents
    uint8_t _attentionFrequency = 100;
    uint8_t _undecayChance = 100;
    uint8_t _healthGainChance = 100;
    uint8_t _mischievousChance = 100;
    uint8_t _wasteToSickChance = 100;
    uint8_t _hungryToSickChance = 100;
};

#endif