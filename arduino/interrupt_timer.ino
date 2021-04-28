#include <Arduino.h>
#include "Adafruit_ZeroTimer.h"
#include "Adafruit_LEDBackpack.h"

#define DISPLAY_ADDRESS 0x70
#define RESET_PIN 4
#define DIMMER_PIN 3

// 7 segment display HT16K33
Adafruit_7segment clockDisplay = Adafruit_7segment();

// Last decimal value written to the display
unsigned long lastTimeDisplayed = -1;

// Brightness toggle
bool bright = true;


// timer for counting seconds
Adafruit_ZeroTimer timer = Adafruit_ZeroTimer(3);

void TC3_Handler() {
  Adafruit_ZeroTimer::timerHandler(3);
}

// the timer callback
volatile unsigned long secondsPassed = 0;
volatile boolean togglePin = false;
void TimerCallback0(void)
{
  secondsPassed += 1;
  digitalWrite(LED_BUILTIN, togglePin);
  togglePin = !togglePin;
}

void ResetCallback() {
  if (secondsPassed != 0) {
    Serial.println("Reset!!!");
    secondsPassed = 0;
  }
}

void setup() {
  
  Serial.begin(115200);
  Serial.println("Counter starting!");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RESET_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RESET_PIN), ResetCallback, FALLING);
  pinMode(DIMMER_PIN, INPUT_PULLUP);
  
  // Set up the flexible compare/prescaler for 1Hz, see Adafruit_ZeroTimer examples
  uint16_t compare = 48000000/1024;
  tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1024;

  // Setup display
  clockDisplay.begin(DISPLAY_ADDRESS);  // pass in the address
  clockDisplay.setBrightness(15);

  // Setup timer
  timer.enable(false);
  timer.configure(prescaler,           // prescaler
          TC_COUNTER_SIZE_16BIT,       // bit width of timer/counter
          TC_WAVE_GENERATION_MATCH_PWM // frequency or PWM mode
          );

  timer.setCompare(0, compare);
  timer.setCallback(true, TC_CALLBACK_CC_CHANNEL0, TimerCallback0);
  timer.enable(true);
}

void loop() {  
  bool dimmerPin = digitalRead(DIMMER_PIN);
  if (bright != dimmerPin) {
    Serial.printf("Dimmer value changed to %s\n", dimmerPin ? "true" : "false");
    bright = dimmerPin;
    if (bright) {
      clockDisplay.setBrightness(15);
    } else {
      clockDisplay.setBrightness(1);
    }
  }
  
  unsigned long time = secondsPassed;

  unsigned long hours = time / (60 * 60);
  unsigned long minutes = (time / 60) % 60;
  unsigned long timeToDisplay = hours * 100 + minutes;
  // Show seconds for the first 10 minutes, then update only every minute
  if ( timeToDisplay < 10 ) {
    clockDisplay.blinkRate(HT16K33_BLINK_OFF);
    clockDisplay.print(timeToDisplay * 100 +  time % 60, DEC);
    clockDisplay.drawColon(time % 2 == 0);
    clockDisplay.writeDisplay();
    lastTimeDisplayed = timeToDisplay;
  } else if ( timeToDisplay != lastTimeDisplayed) { 
    if (timeToDisplay >= 150 && timeToDisplay < 155) {
      clockDisplay.blinkRate(HT16K33_BLINK_1HZ);
    } else if (timeToDisplay >= 155) {
      clockDisplay.blinkRate(HT16K33_BLINK_2HZ);
    }
    
    clockDisplay.print(timeToDisplay, DEC);
    clockDisplay.drawColon(true);
    clockDisplay.writeDisplay();
    Serial.printf("Updated display to %d\n", timeToDisplay);
    lastTimeDisplayed = timeToDisplay;
  }

  delay(100);
}
