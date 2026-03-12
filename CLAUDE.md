# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A count-up timer for an **Adafruit Trinket M0** microcontroller with an **HT16K33 7-segment display** (I2C address 0x70). Designed as a 2-hour pit timer. Displays seconds for the first 10 minutes, then switches to H:MM format. Blinks at 1Hz from 1:50–1:54 and at 2Hz from 1:55 onward.

## Implementations

There are two implementations. **`arduino/interrupt_timer.ino` is the recommended production version** — it uses `Adafruit_ZeroTimer` with TC3 interrupts for accurate 1Hz counting (prescaler DIV1024 on 48MHz clock). The other files have ~1 minute/hour drift:

- `arduino/millis_timer.ino` — uses `millis()`, has drift (legacy/reference only)
- `circuitpython/main.py` — uses `time.monotonic()`, has drift (CircuitPython 3.1.1)

## Deployment

There is no build system. Deploy directly to hardware:

- **Arduino**: Upload `.ino` via Arduino IDE or `arduino-cli` to Trinket M0. Serial debug at 115200 baud.
- **CircuitPython**: Copy `circuitpython/main.py` and `circuitpython/lib/` to the `CIRCUITPY` USB drive.

## Hardware Pinout (Arduino)

| Pin | Function |
|-----|----------|
| 3   | Dimmer/brightness toggle (pull-up) |
| 4   | Reset button (restarts counter from 0, pull-up) |
| SDA/SCL | I2C to HT16K33 display |
| LED_BUILTIN | Blinks in sync with seconds |

## Libraries

- **Arduino**: `Adafruit_ZeroTimer`, `Adafruit_LEDBackpack` (install via Arduino Library Manager)
- **CircuitPython**: `adafruit_ht16k33`, `adafruit_bus_device`, `adafruit_register` (bundled in `circuitpython/lib/`)
