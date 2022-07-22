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
bool btn_A_flag = false;
bool btn_B_flag = false;
bool btn_C_flag = false;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Scheduler ts;
// These 2 get consumed by Animator to trigger animation and sound.
Task animTask(TASK_IMMEDIATE, TASK_ONCE, callbackAnimationWrapper, &ts, true);
Task soundTask(TASK_IMMEDIATE, TASK_ONCE, callbackSoundWrapper, &ts, true);
#ifdef USE_SERIAL
Task statusTask(TASK_SECOND, TASK_FOREVER, showStatus, &ts, true);
#endif
Animator animator(animTask, soundTask, display, SPEAKER_PIN);
Task pandaTask(TASK_IMMEDIATE, 0, [](){Serial.println("Caught pandaTask");}, &ts, true);
Panda panda(pandaTask, display, animator);


void setup() {
  // Do the GPIO
  pinMode(BTN_A_PIN, INPUT_PULLUP);
  pinMode(BTN_B_PIN, INPUT_PULLUP);
  pinMode(BTN_C_PIN, INPUT_PULLUP);
  pinMode(ERROR_LED_PIN, OUTPUT);
  digitalWrite(ERROR_LED_PIN, LOW); 
  
  // Seed the PRNG
  randomSeed(analogRead(0) * millis());

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
}

void loop() {
  //ts.execute();
  panda.displayNeutralState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displaySatisfiedState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displayHappyState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displaySickState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displayWasteState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displayHungryState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displayTiredState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displayAsleepState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displayBoredState();
  delay(1000);
  Serial.println(freeMemory());
  panda.displayFakeNeedsAttentionState();
  delay(1000);
  Serial.println(freeMemory());
}

void error()
{
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

void callbackPandaWrapper()
{
  panda.callback();
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