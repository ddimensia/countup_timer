/*************************************************** 
  This is a library for our I2C LED Backpacks
  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870
  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define DISPLAY_ADDRESS 0x70

Adafruit_7segment clockDisplay = Adafruit_7segment();

unsigned long lastTimeDisplayed = -1;

void setup() {
  Serial.begin(11520);
  Serial.println("Counter starting!");
  
  clockDisplay.begin(DISPLAY_ADDRESS);  // pass in the address
  clockDisplay.setBrightness(15);
}

void loop() {
  unsigned long time = millis();

  unsigned long hours = time / (1000 * 60 * 60);
  unsigned long minutes = (time / (1000 * 60)) % 60;
  unsigned long timeToDisplay = hours * 100 + minutes;
  // Don't bother updating the display unecessarily
  if ( timeToDisplay != lastTimeDisplayed) { 
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
  delay(1000);  
}
