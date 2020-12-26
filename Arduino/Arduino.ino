
// Include Libraries
#include "Arduino.h"
#include "Button.h"

// Pin Definitions
#define RESET_BUTTON	 2

#define COUNT   8
#define SWITCH_1 3
#define SWITCH_2 4
#define SWITCH_3 5
#define SWITCH_4 6
#define SWITCH_5 7
#define SWITCH_6 8
#define SWITCH_7 9
#define SWITCH_8 10

#define LED_1_GREEN 3
#define LED_2_GREEN 4
#define LED_3_GREEN 5
#define LED_4_GREEN 6
#define LED_5_GREEN 7
#define LED_6_GREEN 8
#define LED_7_GREEN 9
#define LED_8_GREEN 10

#define LED_1_RED 3
#define LED_2_RED 4
#define LED_3_RED 5
#define LED_4_RED 6
#define LED_5_RED 7
#define LED_6_RED 8
#define LED_7_RED 9
#define LED_8_RED 10


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
  if (resetButton.onPress())
    stateToBeCompleted = !stateToBeCompleted;

  bool wasComplete = isComplete;

  isComplete = true;
  for (int i = 0; i < COUNT; i++) {
    bool switchState = digitalRead(switches[i]);

    if (switchState != stateToBeCompleted)
      isComplete = false;

    digitalWrite(greenLEDs[i], switchState);
    digitalWrite(redLEDs[i], !switchState);
  }

  if (!wasComplete && isComplete)
    animation();
}

void animation() {
  Serial.println("Animation");
}
