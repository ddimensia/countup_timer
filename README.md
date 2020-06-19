# Countup Timer
Simple count up timer using a Adafruit Trinket M0 and an HT16K33 7 Segment display

This is just a simple implementation of a countup timer that starts at 0 and counts up, 
displaying hours and minutes since the device first powered on.  It's set to start flashing the
time at the 2 hour mark as this was setup for a use case where there was a 2 hour limit on an
activity.

The initial implementation was done with CircuitPython and is in the [circuitpython](circuitpython) directory.  
Simply placing the contents of that directory on a Trinket M0 wired to a HT16K33 display should work
as expected.  I noticed a little drift with the time, about 1 minute per hour, so I intend to build an
Arduino sketch for the device to see if I get different behavior.

There are two Arduino sketchs, first was a straight forward approach using the 'millis()' function and more or
less replicating the circuitpython code.  This exhibited the same clock drift as with circuitpython.  The [interrupt_timer.ino](arduino/interrupt_timer.ino) version uses an interupt on one of the devices timers to count seconds since startup.  This approach appears to yield much better time accuracy, at least enough to have miminal error for the duration I'm trying to measure.
