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
#include "faces.h"
#include "sequences.h"
#include "sounds.h"
#include "notes.h"
#include "freemem.h"
#include "panda.h"

// Globals (TODO localize the scope of these)
uint8_t btn_A_state = HIGH;
uint8_t btn_B_state = HIGH;
uint8_t btn_C_state = HIGH;
uint32_t btn_A_last_transition = 0;
uint32_t btn_B_last_transition = 0;
uint32_t btn_C_last_transition = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Scheduler ts;
// These 2 get consumed by Animator to trigger animation and sound.
Task animTask(TASK_IMMEDIATE, TASK_ONCE, callbackAnimationWrapper, &ts, true);
Task soundTask(TASK_IMMEDIATE, TASK_ONCE, callbackSoundWrapper, &ts, true);
#ifdef USE_SERIAL
//Task statusTask(TASK_SECOND, TASK_FOREVER, showStatus, &ts, true);
#endif
Animator animator(animTask, soundTask, display, SPEAKER_PIN);
Task pandaTask(TASK_IMMEDIATE, 0, callbackPandaWrapper, &ts, true);
Panda panda(pandaTask, display, animator);
Task buttonTask(TASK_MILLISECOND, TASK_FOREVER, btnCheck, &ts, true);
//Task testTask(11000, TASK_FOREVER, test, &ts, true);


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
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);  // Erase background when rendering text
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

  // Seed the PRNG
  uint32_t seed = millis() * analogRead(0);
  #ifdef USE_SERIAL
  Serial.print("Using seed ");
  Serial.println(seed);
  #endif
  srand(seed);

  panda.start();
}

void loop() {
  ts.execute();
}

void error()
{
  tone(SPEAKER_PIN, 1000);
  digitalWrite(ERROR_LED_PIN, HIGH);
  while(true) {};
}

void btnCheck()
{
  // On a state change more than DEBOUNCE_TIME ms since the last state change
  uint8_t a = digitalRead(BTN_A_PIN);
  if (a != btn_A_state && millis() - btn_A_last_transition > DEBOUNCE_TIME)
  {
    btn_A_last_transition = millis();
    btn_A_state = a;
    #ifdef USE_SERIAL
    Serial.print(millis());
    Serial.print(" ");
    #endif
    if (a == HIGH)
    {
      #ifdef USE_SERIAL
      Serial.println(F("Button A UP"));
      #endif
    }
    else
    {
      #ifdef USE_SERIAL
      Serial.println(F("Button A DOWN"));
      #endif
      panda.pressA();
    }
  }

  uint8_t b = digitalRead(BTN_B_PIN);
  if (b != btn_B_state && millis() - btn_B_last_transition > DEBOUNCE_TIME)
  {
    btn_B_last_transition = millis();
    btn_B_state = b;
    #ifdef USE_SERIAL
    Serial.print(millis());
    Serial.print(" ");
    #endif
    if (b == HIGH)
    {
      #ifdef USE_SERIAL
      Serial.println(F("Button B UP"));
      #endif
    }
    else
    {
      #ifdef USE_SERIAL
      Serial.println(F("Button B DOWN"));
      #endif
      panda.pressB();
    }
  }

  uint8_t c = digitalRead(BTN_C_PIN);
  if (c != btn_C_state && millis() - btn_C_last_transition > DEBOUNCE_TIME)
  {
    btn_C_last_transition = millis();
    btn_C_state = c;
    #ifdef USE_SERIAL
    Serial.print(millis());
    Serial.print(" ");
    #endif
    if (c == HIGH)
    {
      #ifdef USE_SERIAL
      Serial.println(F("Button C UP"));
      #endif
    }
    else
    {
      #ifdef USE_SERIAL
      Serial.println(F("Button C DOWN"));
      #endif
      panda.pressC();
    }
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

void callbackPandaWrapper()
{
  panda.callback();
}

void test()
{
  panda.displayNeutralState();
  showStatus();
  delay(1000);
  panda.displaySatisfiedState();
  showStatus();
  delay(1000);
  panda.displayHappyState();
  showStatus();
  delay(1000);
  panda.displaySickState();
  showStatus();
  delay(1000);
  panda.displayWasteState();
  showStatus();
  delay(1000);
  panda.displayHungryState();
  showStatus();
  delay(1000);
  panda.displayTiredState();
  showStatus();
  delay(1000);
  panda.displayAsleepState();
  showStatus();
  delay(1000);
  panda.displayBoredState();
  showStatus();
  delay(1000);
  panda.displayFakeNeedsAttentionState();
  showStatus();
  delay(1000);
}

void showStatus()
{
  #ifdef USE_SERIAL
  Serial.print(millis());
  Serial.print("ms ");
  Serial.print(freeMemory());
  Serial.println(" bytes free");
  #endif
  display.setCursor(20, 0);
  display.println(millis());
  display.display();
}