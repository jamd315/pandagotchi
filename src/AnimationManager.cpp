#include <avr/pgmspace.h>
#include "AnimationManager.h"
#include "globals.h"


Animator::Animator(Task &animTask, Task &soundTask, Adafruit_SSD1306 &display, uint8_t speakerPin): _animTask(animTask), _soundTask(soundTask), _display(display), _speakerPin(speakerPin)
{

}

void Animator::callbackAnimation()
{
  #ifdef USE_SERIAL
  Serial.println(F("Callback triggered"));
  #endif
  if (activeAnimationElement == nullptr)
  {
    #ifdef USE_SERIAL
    Serial.println(F("End of sequence"));
    #endif
    return;
  }
  drawActiveAnimationElement();
  _animTask.restartDelayed(getActiveDelay());
  activeAnimationElement = getNext();
}

void Animator::callbackSound()
{

}

// Starts displaying the given Animation
void Animator::startAnimationSequence(const AnimationSequence &sequence)
{
  #ifdef USE_SERIAL
  Serial.print(F("Starting sequence "));
  Serial.println(sequence.id);
  #endif
  activeAnimationElement = (AnimationElement*) pgm_read_ptr(&sequence.head);
  callbackAnimation();
}

// Merged the memory and PROGMEM versions of Adafruit GFXs drawBitmap, plus incorporated references to activeAnimationElement rather than parameters.
// Around here https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L751
void Animator::drawActiveAnimationElement()
{
  #ifdef USE_SERIAL
  Serial.println(F("Called drawActiveAnimationElement"));
  Serial.print(F("x="));
  Serial.print(getActiveX());
  Serial.print(F(" y="));
  Serial.print(getActiveY());
  Serial.print(F(" w="));
  Serial.print(getActiveW());
  Serial.print(F(" h="));
  Serial.print(getActiveH());
  Serial.print(F(" delay="));
  Serial.println(getActiveDelay());
  #endif
  int16_t byteWidth = (getActiveW() + 7) / 8;
  uint8_t b = 0;
  int16_t x = getActiveX();
  int16_t y = getActiveY();
  const uint8_t *image = getActiveImage();
  bool clearDisplay = getActiveMeta() & IMAGE_CLEARDISPLAY;
  bool transparent = getActiveMeta() & IMAGE_TRANSPARENT;
  bool invert = getActiveMeta() & IMAGE_INVERT;

  // Clear if needed
  if (clearDisplay)
    _display.clearDisplay();

  // Handle colors
  uint8_t fgColor = 1;
  uint8_t bgColor = 0;
  if (invert)
  {
    fgColor = 0;
    bgColor = 1;
  }

  _display.startWrite();
  for(int16_t j = 0; j < getActiveH(); j++, y++)
  {
    for(int16_t i = 0; i < getActiveW(); i++)
    {
      if (i & 7)
        b <<= 1;
      else
        b = pgm_read_byte(&image[j * byteWidth + i / 8]);
      if (b & 0x80)  // Always draw the foreground pixels
      {
        _display.writePixel(x + i, y, fgColor);
      }
      else if (!transparent)  // Only draw the background pixels if not transparent, TODO might be problematic with inverted images?
      {
        _display.writePixel(x + i, y, bgColor);
      }
    }
  }
  _display.endWrite();
  _display.display();  // TODO maybe add this to meta?
}

// Helper function to access x value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getActiveX()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->x));
}

// Helper function to access y value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getActiveY()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->y));
}

// Helper function to access w value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getActiveW()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->w));
}

// Helper function to access h value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getActiveH()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->h));
}

// Helper function to access meta value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getActiveMeta(){
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->meta));
}

// Helper function to access delay value of the activeAnimationElement in PROGMEM
inline uint16_t Animator::getActiveDelay()
{
  return (uint16_t) pgm_read_word(&(activeAnimationElement->delay));
}

inline const uint8_t *Animator::getActiveImage()
{
  return (const uint8_t *) pgm_read_ptr(&(activeAnimationElement->image));
}

inline AnimationElement *Animator::getNext()
{
  return (AnimationElement *) pgm_read_ptr(&(activeAnimationElement->next));
}


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
