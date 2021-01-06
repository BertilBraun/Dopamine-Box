
// Include Libraries
#include "Arduino.h"
#include "Button.h"

// Pin Definitions
#define RESET_BUTTON     12

#define COUNT   8
#define SWITCH_1 10
#define SWITCH_2 9
#define SWITCH_3 8
#define SWITCH_4 7
#define SWITCH_5 6
#define SWITCH_6 5
#define SWITCH_7 4
#define SWITCH_8 3

#define LED_1_GREEN 25
#define LED_2_GREEN 29
#define LED_3_GREEN 33
#define LED_4_GREEN 37
#define LED_5_GREEN 41
#define LED_6_GREEN 45
#define LED_7_GREEN 49
#define LED_8_GREEN 53

#define LED_1_RED 22
#define LED_2_RED 26
#define LED_3_RED 30
#define LED_4_RED 34
#define LED_5_RED 38
#define LED_6_RED 42
#define LED_7_RED 46
#define LED_8_RED 50


// Global variables and defines

// object initialization
Button resetButton(RESET_BUTTON);

int switches[COUNT] {
  SWITCH_1,
  SWITCH_2,
  SWITCH_3,
  SWITCH_4,
  SWITCH_5,
  SWITCH_6,
  SWITCH_7,
  SWITCH_8,
};

int greenLEDs[COUNT] {
  LED_1_GREEN,
  LED_2_GREEN,
  LED_3_GREEN,
  LED_4_GREEN,
  LED_5_GREEN,
  LED_6_GREEN,
  LED_7_GREEN,
  LED_8_GREEN,
};

int redLEDs[COUNT] {
  LED_1_RED,
  LED_2_RED,
  LED_3_RED,
  LED_4_RED,
  LED_5_RED,
  LED_6_RED,
  LED_7_RED,
  LED_8_RED,
};

bool isComplete = false;
bool stateToBeCompleted = true;
int maxBrightness = 128;
int maxBrightnessInAnimation = 255;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  Serial.println("start");

  resetButton.init();
  for (int swt : switches)
    pinMode(swt, INPUT);

  for (int led : greenLEDs)
    pinMode(led, OUTPUT);

  for (int led : redLEDs)
    pinMode(led, OUTPUT);
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
  if (resetButton.onPress()) {
    Serial.println("Button Pressed!");
    stateToBeCompleted = !stateToBeCompleted;
  }

  // FUCK THIS SHEIT, this should not have to be here... Where is the pinmode for switches[0] changed?!?!?!
  // IDC
  pinMode(switches[0], INPUT);
   
  bool wasComplete = isComplete;

  isComplete = true;
  for (int i = 0; i < COUNT; i++) {
    bool switchState = digitalRead(switches[i]);

    if (switchState != stateToBeCompleted)
      isComplete = false;

    if (switchState == stateToBeCompleted) {
      analogWrite(greenLEDs[i], maxBrightness);
      analogWrite(redLEDs[i], 0);
    } else {
      analogWrite(greenLEDs[i], 0);
      analogWrite(redLEDs[i], maxBrightness);
    }
  }

  if (!wasComplete && isComplete)
    animation();
}

void animation() {
  Serial.println("Animation");

  for (int c = 2; c > 0; c--) {
    for (int i = 0; i < COUNT; i++) {
      for (int j = 0; j < COUNT; j++)
        analogWrite(greenLEDs[j], 0);
      analogWrite(greenLEDs[i], maxBrightness);
      delay(25 * c);
    }

    for (int i = 0; i < COUNT; i++) {
      for (int j = 0; j < COUNT; j++)
        analogWrite(greenLEDs[j], 0);
      analogWrite(greenLEDs[COUNT - i], maxBrightness);
      delay(25 * c);
    }
  }
}
