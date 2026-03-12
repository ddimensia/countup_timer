# Countup Timer

A simple count-up timer using an [Adafruit Trinket M0](https://www.adafruit.com/product/3500) and an [HT16K33 7-Segment display](https://www.adafruit.com/product/1270).

The timer starts at zero, counts up by seconds for the first 10 minutes, then switches to hours:minutes format. It begins flashing at the 1 hour 50 minute mark — designed for use cases with a 2-hour activity limit. This works well as a pit timer when the device is on battery backup and the driver resets the clock on pit-in.

## Recommended Implementation

Use **[`arduino/interrupt_timer.ino`](arduino/interrupt_timer.ino)** — it is the most accurate and up-to-date version. It uses a hardware interrupt on the Trinket M0's TC3 timer to count seconds, which eliminates the clock drift present in the other implementations.

## Development History

### CircuitPython (first attempt)

The initial implementation is in the [`circuitpython`](circuitpython) directory. Placing the contents of that directory onto a Trinket M0 wired to an HT16K33 display is all that's needed to run it. However, this version exhibits roughly **1 minute of drift per hour** due to how `time.monotonic()` accumulates timing error.

### Arduino: millis() (second attempt)

The first Arduino sketch ([`arduino/millis_timer.ino`](arduino/millis_timer.ino)) took a straightforward approach by replicating the CircuitPython logic using the `millis()` function. It exhibited the same clock drift as the CircuitPython version.

### Arduino: interrupt timer (current)

[`arduino/interrupt_timer.ino`](arduino/interrupt_timer.ino) uses a hardware interrupt on the device's TC3 timer to count seconds since startup. This approach yields significantly better accuracy — minimal error over the 2-hour duration being measured.
