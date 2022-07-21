#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TaskScheduler.h>
#include "main.h"
#include "globals.h"
#include "Animator.h"
#include "images.h"
#include "sequences.h"
#include "notes.h"
#include "freemem.h"

// Globals (TODO localize the scope of these)
uint8_t btn_A_state = HIGH;
uint8_t btn_B_state = HIGH;
uint8_t btn_C_state = HIGH;
uint32_t btn_A_last_transition = 0;
uint32_t btn_B_last_transition = 0;
uint32_t btn_C_last_transition = 0;
bool btn_A_flag = false;
bool btn_B_flag = false;
bool btn_C_flag = false;

const uint8_t *menuBitmaps[] = {food, light, play, doctor, toilet, info, discipline, attention};
uint8_t menuIndex = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Scheduler ts;
// These 2 get consumed by Animator to trigger animation and sound.
Task animTask(TASK_IMMEDIATE, TASK_ONCE, callbackAnimationWrapper, &ts, true);
Task soundTask(TASK_IMMEDIATE, TASK_ONCE, callbackSoundWrapper, &ts, true);
#ifdef USE_SERIAL
Task statusTask(TASK_SECOND, TASK_FOREVER, showStatus, &ts, true);
#endif
Task notNamingThis(8000, TASK_FOREVER, testAnimator, &ts, true);
Animator animator(animTask, soundTask, display, SPEAKER_PIN);


void setup() {
  // Do the GPIO
  pinMode(BTN_A_PIN, INPUT_PULLUP);
  pinMode(BTN_B_PIN, INPUT_PULLUP);
  pinMode(BTN_C_PIN, INPUT_PULLUP);
  pinMode(ERROR_LED_PIN, OUTPUT);
  digitalWrite(ERROR_LED_PIN, LOW); 
  
  // Start the SSD 1306 display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    error();
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.cp437(true);
  display.println("Display started");
  display.display();

  // Set up Serial if enabled
  #ifdef USE_SERIAL
  Serial.begin(9600);
  while(!Serial);  // While necessary-ish for Serial, this gets in the way of the task scheduler.
  Serial.println(F("Serial enabled"));
  #endif
  testAnimator();
}

void loop() {
  ts.execute();
}

void error()
{
  digitalWrite(ERROR_LED_PIN, HIGH);
  while(true) {};
}

void drawMenu()
{
  // Draws the menu but does NOT display it
  for (size_t i = 0; i < sizeof menuBitmaps / sizeof menuBitmaps[0]; i++)
  {
    display.drawBitmap(getMenuX(i), getMenuY(i), menuBitmaps[i], ICON_WIDTH, ICON_HEIGHT, 1, 0);
  }
  // Draw selection with inverted colors
  display.drawBitmap(getMenuX(menuIndex), getMenuY(menuIndex), menuBitmaps[menuIndex], ICON_WIDTH, ICON_HEIGHT, 0, 1);
}

uint8_t getMenuX(uint8_t index)
{
  if (index < 4)
    return 0;
  else
    return display.width() - ICON_WIDTH;
}

uint8_t getMenuY(uint8_t index)
{
  return ICON_HEIGHT * (index % 4);
}

void btnCheck()
{
  // On a state change more than DEBOUNCE_TIME ms since the last state change
  uint8_t a = digitalRead(BTN_A_PIN);
  if (a != btn_A_state && millis() - btn_A_last_transition > DEBOUNCE_TIME)
  {
    btn_A_last_transition = millis();
    btn_A_state = a;
    btn_A_flag = true;
    #ifdef USE_SERIAL
    Serial.print(millis());
    Serial.print(" ");
    if (a == HIGH)
      Serial.println(F("Button A UP"));
    else
      Serial.println(F("Button A DOWN"));
    #endif
  }

  uint8_t b = digitalRead(BTN_B_PIN);
  if (b != btn_B_state && millis() - btn_B_last_transition > DEBOUNCE_TIME)
  {
    btn_B_last_transition = millis();
    btn_B_state = b;
    btn_B_flag = true;
    #ifdef USE_SERIAL
    Serial.print(millis());
    Serial.print(" ");
    if (b == HIGH)
      Serial.println(F("Button B UP"));
    else
      Serial.println(F("Button B DOWN"));
    #endif
  }

  uint8_t c = digitalRead(BTN_C_PIN);
  if (c != btn_C_state && millis() - btn_C_last_transition > DEBOUNCE_TIME)
  {
    btn_C_last_transition = millis();
    btn_C_state = c;
    btn_C_flag = true;
    #ifdef USE_SERIAL
    Serial.print(millis());
    Serial.print(" ");
    if (c == HIGH)
      Serial.println(F("Button C UP"));
    else
      Serial.println(F("Button C DOWN"));
    #endif
  }
}

void callbackAnimationWrapper()
{
  animator.callbackAnimation();
}

void callbackSoundWrapper()
{
  animator.callbackSound();
}

void testAnimator()
{
  animator.startAnimationSequence(testAnimation);
}

#ifdef USE_SERIAL
void showStatus()
{
  Serial.print(millis());
  Serial.print("ms ");
  Serial.print(freeMemory());
  Serial.println(" bytes free");
}
#endif