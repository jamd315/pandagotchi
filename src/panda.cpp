#include <Arduino.h>
#include "globals.h"
#include "panda.h"
#include "Animator.h"
#include "images.h"

const uint8_t *_menuBitmaps[] = {food, light, play, doctor, toilet, info, discipline, attention};

Panda::Panda(Task &pandaStateTask, Adafruit_SSD1306 &display, Animator &animator): _pandaStateTask(pandaStateTask), _display(display), _animator(animator)
{
    _weights =
    {
        .FakeNeedAttention = 12,
        .Sick = 8,
        .Waste = 32,
        .Hungry = 64,
        .Tired = 32,
        .Bored = 64 
    };
    //transitionNeutralState();
};

PandaState Panda::getNewRandomState()
{
    uint16_t sumOfWeights = _weights.FakeNeedAttention + _weights.Sick + _weights.Waste + _weights.Hungry + _weights.Tired + _weights.Bored;
    
    // Sort of a non-loop or unrolled loop version of a weighted random algorithm
    uint16_t choice = sumOfWeights * (1.0 * rand() / RAND_MAX);
    Serial.println(choice);

    if (choice < _weights.FakeNeedAttention)
        return FAKE_NEED_ATTENTION;
    choice -= _weights.FakeNeedAttention;

    if (choice < _weights.Sick)
        return SICK;
    choice -= _weights.Sick;

    if (choice < _weights.Waste)
        return WASTE;
    choice -= _weights.Waste;

    if (choice < _weights.Hungry)
        return HUNGRY;
    choice -= _weights.Hungry;

    if (choice < _weights.Tired)
        return TIRED;
    choice -= _weights.Tired;

    if (choice < _weights.Bored)
        return BORED;
    choice -= _weights.Bored;

    return NEUTRAL;  // Theoretically never gets called, but if it does just return to NEUTRAL state
}


#pragma region transitions
void Panda::transitionNewRandomState()
{
    PandaState newState = getNewRandomState();
    switch (newState)
    {        
        case FAKE_NEED_ATTENTION:
            transitionFakeNeedsAttentionState();
            break;
        
        case SICK:
            transitionSickState();
            break;
        
        case WASTE:
            transitionWasteState();
            break;
        
        case HUNGRY:
            transitionHungryState();
            break;
        
        case TIRED:
            transitionTiredState();
            break;
        
        case BORED:
            transitionBoredState();
            break;

        default:
            #ifdef USE_SERIAL
            Serial.print(F("Got unexpected state "));
            Serial.println(newState);
            #endif
            transitionNeutralState();
            break;
    }
}

void Panda::transitionNeutralState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to NEUTRAL "));
    #endif
    _state = NEUTRAL;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = false;
    displayNeutralState();
    _pandaStateTask.restartDelayed(getDelayLong());
}

void Panda::transitionSatisfiedState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to SATISFIED "));
    #endif
    _state = SATISFIED;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = false;
    displaySatisfiedState();
    _pandaStateTask.restartDelayed(getDelayMedium());
}

void Panda::transitionHappyState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to HAPPY "));
    #endif
    _state = HAPPY;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = false;
    displayHappyState();
    _pandaStateTask.restartDelayed(getDelayMedium());
}

void Panda::transitionSickState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to SICK "));
    #endif
    _state = SICK;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = true;
    displaySickState();
    _pandaStateTask.restartDelayed(getDelayMedium());
}

void Panda::transitionWasteState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to WASTE "));
    #endif
    _state = WASTE;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = true;
    displayWasteState();
    _pandaStateTask.restartDelayed(getDelayShort());
}

void Panda::transitionHungryState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to HUNGRY "));
    #endif
    _state = HUNGRY;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = true;
    displayHungryState();
    _pandaStateTask.restartDelayed(getDelayMedium());
}

void Panda::transitionTiredState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to TIRED "));
    #endif
    _state = TIRED;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = true;
    displayTiredState();
    _pandaStateTask.restartDelayed(getDelayShort());
}

void Panda::transitionAsleepState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to ASLEEP "));
    #endif
    _state = ASLEEP;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = false;
    displayAsleepState();
    _sleepStartTime = millis();
    _pandaStateTask.restartDelayed(getDelayLong());
}

void Panda::transitionBoredState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to BORED "));
    #endif
    _state = BORED;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = true;
    displayBoredState();
    _pandaStateTask.restartDelayed(getDelayMedium());
}

void Panda::transitionFakeNeedsAttentionState()
{
    #ifdef USE_SERIAL
    Serial.print(F("State transition from "));
    Serial.print(_state);
    Serial.print(F(" to FNA "));
    #endif
    _state = FAKE_NEED_ATTENTION;
    #ifdef USE_SERIAL
    Serial.println(_state);
    #endif
    _attentionFlag = true;
    displayFakeNeedsAttentionState();
    _pandaStateTask.restartDelayed(getDelayMedium());
}
#pragma endregion transitions


#pragma region callbacks
void Panda::callback()
{
    switch (_state)
    {
        case NEUTRAL:
            callbackNeutralState();
            break;
        
        case SATISFIED:
            callbackSatisfiedState();
            break;
        
        case HAPPY:
            callbackHappyState();
            break;
        
        case SICK:
            callbackSickState();
            break;
        
        case WASTE:
            callbackWasteState();
            break;
        
        case HUNGRY:
            callbackHappyState();
            break;
        
        case TIRED:
            callbackTiredState();
            break;
        
        case ASLEEP:
            callbackTiredState();
            break;
        
        case BORED:
            callbackBoredState();
            break;
        
        case FAKE_NEED_ATTENTION:
            callbackFakeNeedsAttentionState();
            break;
        
        default:
            #ifdef USE_SERIAL
            Serial.print(F("Got unhandled state "));
            Serial.println(_state);
            #endif
            transitionNeutralState();
            break;
    }
}

void Panda::callbackNeutralState()
{
    if (rand() % 100 < (UNDECAY_CHANCE * _undecayChance / 100))
    {
        transitionSatisfiedState();
    }
    else
    {
        transitionNewRandomState();
    }
}

void Panda::callbackSatisfiedState()
{
    if (rand() % 100 < (UNDECAY_CHANCE * _undecayChance / 100))
    {
        transitionHappyState();
    }
    else
    {
        transitionNeutralState();
    }
}

void Panda::callbackHappyState()
{
    // Possibility to gain health after being happy
    if (rand() % 100 < (HEALTH_GAIN_CHANCE * _healthGainChance / 100))
    {
        if (_health < 10)
        {
            _health++;
        }
    }

    if (rand() % 100 < (MISCHIEVIOUS_CHANCE * _mischievousChance / 100))
    {
        transitionFakeNeedsAttentionState();
    }
    else
    {
        transitionSatisfiedState();
    }
}

void Panda::callbackSickState()
{
    // Happens when SICK status hasn't been addressed
    _health--;
    transitionSickState();
}

void Panda::callbackWasteState()
{
    // Happens when WASTE status hasn't been addressed
    if (rand() % 100 < (WASTE_TO_SICK_CHANCE * _wasteToSickChance / 100))
    {
        transitionSickState();
    }
    else
    {
        transitionWasteState();
    }
}

void Panda::callbackHungryState()
{
    // Happens when HUNGRY state hasn't been addressed
    if (rand() % 100 < (HUNGRY_TO_SICK_CHANCE * _hungryToSickChance / 100))
    {
        transitionSickState();
    }
    else
    {
        transitionHungryState();
    }
}

void Panda::callbackTiredState()
{
    if (!_lightsOn)
    {
        transitionAsleepState();
    }
    else
    {
        // Check back shortly if the lights are off
        _pandaStateTask.restartDelayed(getDelayShort());
    }
}

void Panda::callbackAsleepState()
{
    if (millis() - _sleepStartTime > SLEEP_TIME)
    {
        transitionSatisfiedState();
    }
    else
    {
        // Check back in a bit if still asleep
        _pandaStateTask.restartDelayed(getDelayLong());
    }
}

void Panda::callbackBoredState()
{
    _mischievousChance = clampedModify(_mischievousChance, 5);
    _pandaStateTask.restartDelayed(getDelayMedium());
}

void Panda::callbackFakeNeedsAttentionState()
{
    _mischievousChance = clampedModify(_mischievousChance, -1);  // Slightly decrease for successfully ignoring negative state
    transitionNeutralState();
}
#pragma endregion callbacks


#pragma region displays
void Panda::displayNeutralState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, neutral, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Neutral"));
    _display.display();
}

void Panda::displaySatisfiedState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, satisfied, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Satisfied"));
    _display.display();
}

void Panda::displayHappyState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, happy, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Happy"));
    _display.display();
}

void Panda::displaySickState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, sick, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Sick"));
    _display.display();
}

void Panda::displayWasteState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, bored, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.drawBitmap(WASTE_LEFT, WASTE_TOP, waste, ICON_WIDTH, ICON_HEIGHT, _fgColor);
    _display.setCursor(32, 56);
    _display.println(F("Waste"));
    _display.display();
}

void Panda::displayHungryState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, hungry, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Hungry"));
    _display.display();
}

void Panda::displayTiredState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, tired, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Tired"));
    _display.display();
}

void Panda::displayAsleepState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, asleep, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Asleep"));
    _display.display();
}

void Panda::displayBoredState()
{
    _display.clearDisplay();
    drawMenu();
    _display.drawBitmap(FACE_LEFT, FACE_TOP, bored, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("Bored"));
    _display.display();
}

void Panda::displayFakeNeedsAttentionState()
{
    _display.clearDisplay();
    drawMenu();
    // TODO randomly pick a fake attention image
    _display.drawBitmap(FACE_LEFT, FACE_TOP, hungry, FACE_WIDTH, FACE_HEIGHT, _fgColor, _bgColor);
    _display.setCursor(32, 56);
    _display.println(F("FNA"));
    _display.display();
}

void Panda::drawMenu()
{
  // Draws the menu but does NOT display it
  for (size_t i = 0; i < sizeof _menuBitmaps / sizeof _menuBitmaps[0]; i++)
  {
    _display.drawBitmap(getMenuX(i), getMenuY(i), _menuBitmaps[i], ICON_WIDTH, ICON_HEIGHT, _fgColor, _bgColor);
  }
  // Draw selection with inverted colors
  if (_menuIndex != NO_MENU_INDEX)
  {
    _display.drawBitmap(getMenuX(_menuIndex), getMenuY(_menuIndex), _menuBitmaps[_menuIndex], ICON_WIDTH, ICON_HEIGHT, _bgColor, _fgColor);
  }
  // TODO temp debugging
  _menuIndex++;
  _menuIndex %= 7;
  // Show needs attention if _attentionFlag
  if (_attentionFlag)
  {
    _display.drawBitmap(getMenuX(7), getMenuY(7), attention, ICON_WIDTH, ICON_HEIGHT, _bgColor, _fgColor);
  }
  _display.fillRect(16, 0, 16, 64, _bgColor);
  _display.fillRect(96, 0, 16, 64, _bgColor);
}

uint8_t Panda::getMenuX(uint8_t index)
{
  if (index < 4)
    return 0;
  else
    return _display.width() - ICON_WIDTH;
}

uint8_t Panda::getMenuY(uint8_t index)
{
  return ICON_HEIGHT * (index % 4);
}
#pragma endregion displays


uint32_t Panda::getDelayLong()
{
    uint32_t delay = (1.0 * _attentionFrequency / 100) * (DELAY_LONG_LOW + (DELAY_LONG_HIGH - DELAY_LONG_LOW) * (1.0 * rand() / RAND_MAX));
    #ifdef USE_SERIAL
    Serial.print(F("Got long delay of "));
    Serial.println(delay);
    #endif
    return delay;
}

uint32_t Panda::getDelayMedium()
{
    uint32_t delay = (1.0 * _attentionFrequency / 100) * (DELAY_MEDIUM_LOW + (DELAY_MEDIUM_HIGH - DELAY_MEDIUM_LOW) * (1.0 * rand() / RAND_MAX));
    #ifdef USE_SERIAL
    Serial.print(F("Got medium delay of "));
    Serial.println(delay);
    #endif
    return delay;
}

uint32_t Panda::getDelayShort()
{
    uint32_t delay = (1.0 * _attentionFrequency / 100) * (DELAY_SHORT_LOW + (DELAY_SHORT_HIGH - DELAY_SHORT_LOW) * (1.0 * rand() / RAND_MAX));
    #ifdef USE_SERIAL
    Serial.print(F("Got short delay of "));
    Serial.println(delay);
    #endif
    return delay;
}

inline void Panda::lightsOn()
{
    // Black on white, looks bright
    _fgColor = SSD1306_BLACK;
    _bgColor = SSD1306_WHITE;
    _lightsOn = true;
}

inline void Panda::lightsOff()
{
    // White lights on black, looks dark
    _fgColor = SSD1306_WHITE;
    _bgColor = SSD1306_BLACK;
    _lightsOn = false;
}

inline uint8_t Panda::clampedModify(uint8_t weight, int16_t difference)
{
    if (weight + difference > UINT8_MAX)
        return UINT8_MAX;
    if (weight < (-1 * difference))
        return 0;
    return weight + difference;
}