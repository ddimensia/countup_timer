# Trinket IO demo
# Welcome to CircuitPython 3.1.1 :)

import board
# Import all board pins and bus interface.
import board
import busio

# Import the HT16K33 LED matrix module.
from adafruit_ht16k33 import segments
from digitalio import DigitalInOut, Direction, Pull
import time

# Built in red LED
led = DigitalInOut(board.D13)
led.direction = Direction.OUTPUT

# Create the I2C interface.
i2c = busio.I2C(board.SCL, board.SDA)

# Create the matrix class.
# This creates a 16x8 matrix:
display = segments.Seg7x4(i2c)

# Clear the matrix.
display.fill(0)
# Set the brighness
display.brightness = 15 
display.blink_rate = 0

######################### HELPERS ##############################


######################### MAIN LOOP ##############################
while True:
  now = time.monotonic()

  led.value = 1 if (now % 2) >= 1 else 0

  total_minutes = int(now/60)
  if total_minutes > 110:
    display.blink_rate = 3
  
  minutes = total_minutes % 60
  hours = int(total_minutes/60)
  digit1 = minutes % 10
  digit2 = " " if minutes < 10 and hours == 0 else int(minutes/10)
  digit3 = " " if hours == 0 else int(hours%10)
  digit4 = " "
 
  display.print("{}{}:{}{}".format(digit4,digit3,digit2,digit1))
  

  time.sleep(0.1) # make bigger to slow down
