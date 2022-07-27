#include <avr/pgmspace.h>
#include "Animator.h"
#include "globals.h"


Animator::Animator(Task &animTask, Task &soundTask, Adafruit_SSD1306 &display, uint8_t speakerPin): _animTask(animTask), _soundTask(soundTask), _display(display), _speakerPin(speakerPin)
{

}

void Animator::callbackAnimation()
{
  uint32_t startTime = millis();
  #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
  Serial.println(F("Animation callback triggered"));
  #endif
  if (activeAnimationElement == nullptr)
  {
    #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
    Serial.println(F("End of animation sequence"));
    #endif
    return;
  }
  drawActiveAnimationElement();
  uint32_t endTime = millis();
  uint16_t drawTime = endTime - startTime;
  #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
  Serial.print(F("Completed draw in "));
  Serial.print(drawTime);
  Serial.println(F("ms"));
  #endif
  int32_t delay = getAnimDelay() - drawTime;
  if (delay < 0)
    delay = 0;
  _animTask.restartDelayed(delay);
  activeAnimationElement = getAnimNext();
}

void Animator::callbackSound()
{
  #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
  Serial.println(F("Sound callback triggered"));
  #endif
  if (activeSoundElement == nullptr)
  {
    #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
    Serial.println(F("End of sound sequence"));
    #endif
    return;
  }
  #ifdef USE_SOUND
  tone(_speakerPin, getSoundFrequency(), getSoundDuration());
  #endif
  _soundTask.restartDelayed(getSoundDuration() + getSoundDelay());
  activeSoundElement = getSoundNext();
}

// Starts displaying the given Animation
void Animator::startAnimationSequence(const AnimationSequence &sequence, bool invert)
{
  _sequenceInvert = invert;
  #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
  Serial.print(F("Starting animation sequence "));
  Serial.println(sequence.id);
  #endif
  activeAnimationElement = (AnimationElement*) pgm_read_ptr(&sequence.head);
  callbackAnimation();
}

void Animator::showFace(const AnimationSequence &face, bool invert)
{
  _animTask.disable();
  const AnimationElement *oldElement = activeAnimationElement;
  bool prevSequenceInvert = _sequenceInvert;
  _sequenceInvert = invert;
  activeAnimationElement = (AnimationElement*) pgm_read_ptr(&face.head);
  while (activeAnimationElement != nullptr)
  {
    drawActiveAnimationElement();
    activeAnimationElement = getAnimNext();
  }
  _sequenceInvert = prevSequenceInvert;
  activeAnimationElement = oldElement;
  _animTask.enable();
}

void Animator::startSoundSequence(const SoundSequence &sequence)
{
  #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
  Serial.print(F("Starting sound sequence "));
  Serial.println(sequence.id);
  #endif
  activeSoundElement = (SoundElement *) pgm_read_ptr(&sequence.head);
  callbackSound();
}

// Merged the memory and PROGMEM versions of Adafruit GFXs drawBitmap, plus incorporated references to activeAnimationElement rather than parameters.
// Around here https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp#L751
void Animator::drawActiveAnimationElement()
{
  #if defined USE_SERIAL && defined USE_SERIAL_ANIMATOR
  Serial.println(F("Called drawActiveAnimationElement"));
  Serial.print(F("x="));
  Serial.print(getAnimX());
  Serial.print(F(" y="));
  Serial.print(getAnimY());
  Serial.print(F(" w="));
  Serial.print(getAnimW());
  Serial.print(F(" h="));
  Serial.print(getAnimH());
  Serial.print(F(" delay="));
  Serial.println(getAnimDelay());
  #endif
  int16_t byteWidth = (getAnimW() + 7) / 8;
  uint8_t b = 0;
  int16_t x = getAnimX();
  int16_t y = getAnimY();
  const uint8_t *image = getActiveImage();
  uint8_t meta = getAnimMeta();
  bool clearDisplay = meta & IMAGE_CLEARDISPLAY;
  bool transparent = meta & IMAGE_TRANSPARENT;
  bool elementInvert = meta & IMAGE_INVERT;
  bool drawOnly = meta & IMAGE_DRAWONLY;

  // Clear if needed
  if (clearDisplay)
    _display.clearDisplay();

  // Handle colors
  uint8_t fgColor = 1;
  uint8_t bgColor = 0;
  if (elementInvert != _sequenceInvert)  // XOR basically
  {
    fgColor = 0;
    bgColor = 1;
  }

  _display.startWrite();
  for(int16_t j = 0; j < getAnimH(); j++, y++)
  {
    for(int16_t i = 0; i < getAnimW(); i++)
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
  if (!drawOnly)
  {
    _display.display();
  }
}

// Helper function to access x value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getAnimX()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->x));
}

// Helper function to access y value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getAnimY()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->y));
}

// Helper function to access w value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getAnimW()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->w));
}

// Helper function to access h value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getAnimH()
{
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->h));
}

// Helper function to access meta value of the activeAnimationElement in PROGMEM
inline uint8_t Animator::getAnimMeta(){
  return (uint8_t) pgm_read_byte(&(activeAnimationElement->meta));
}

// Helper function to access delay value of the activeAnimationElement in PROGMEM
inline uint16_t Animator::getAnimDelay()
{
  return (uint16_t) pgm_read_word(&(activeAnimationElement->delay));
}

// Helper function to access image pointer of the activeAnimationElement in PROGMEM
inline const uint8_t *Animator::getActiveImage()
{
  return (const uint8_t *) pgm_read_ptr(&(activeAnimationElement->image));
}

// Helper function to access next AnimationElement
inline AnimationElement *Animator::getAnimNext()
{
  return (AnimationElement *) pgm_read_ptr(&(activeAnimationElement->next));
}

// Helper function to access frequency of the activeSoundElement in PROGMEM
inline uint16_t Animator::getSoundFrequency()
{
  return (uint16_t) pgm_read_word(&(activeSoundElement->frequency));
}

// Helper function to access duration of the activeSoundElement in PROGMEM
inline uint16_t Animator::getSoundDuration()
{
  return (uint16_t) pgm_read_word(&(activeSoundElement->duration));
}

// Helper function to access delay of the activeSoundElement in PROGMEM
inline uint16_t Animator::getSoundDelay()
{
  return (uint16_t) pgm_read_word(&(activeSoundElement->delay));
}

// Helper function to access next SoundElement
inline SoundElement *Animator::getSoundNext()
{
  return (SoundElement *) pgm_read_ptr(&(activeSoundElement->next));
}
