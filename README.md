# Embedded Software/Firmware Engineering — Exercises

Hands-on exercises tracking the mastery roadmap in [Roadmap.md](Roadmap.md). The active
milestone is described in [Level_1_Current.md](Level_1_Current.md).

Board: Arduino Uno (ATmega328P), programmed with raw register writes — no Arduino
libraries or HAL.

## Prerequisites

Install the AVR bare-metal toolchain:

- **avr-gcc** — compiler
- **avr-libc** — headers (`avr/io.h`, `util/delay.h`, etc.)
- **avrdude** — uploads compiled firmware to the board over USB

Windows: easiest path is installing the [Arduino IDE](https://www.arduino.cc/en/software),
which bundles avr-gcc/avrdude — add its `hardware/tools/avr/bin` folder to your `PATH`.
Alternatively, use [MSYS2](https://www.msys2.org/):
`pacman -S mingw-w64-x86_64-avr-gcc avr-libc avrdude`.

macOS: `brew install avr-gcc avrdude`

Linux: `sudo apt install gcc-avr avr-libc avrdude`

Verify installation:

```sh
avr-gcc --version
avrdude -v
```

## Compile

Each exercise lives in its own folder (e.g. `level1_raw_blink/`) and contains a single
`.c` file. From that folder:

```sh
avr-gcc -mmcu=atmega328p -Os -o blink.elf blink.c
avr-objcopy -O ihex -R .eeprom blink.elf blink.hex
```

- `-mmcu=atmega328p` targets the Uno's chip.
- `-Os` optimizes for size (typical for embedded targets).
- `avr-objcopy` converts the ELF binary into the Intel HEX format avrdude expects.

## Upload

Find your board's serial port, then flash it:

```sh
avrdude -c arduino -p atmega328p -P <PORT> -b 115200 -U flash:w:blink.hex:i
```

- Windows: `<PORT>` looks like `COM3` (check Device Manager under "Ports").
- macOS/Linux: `<PORT>` looks like `/dev/tty.usbmodem*` or `/dev/ttyACM0` / `/dev/ttyUSB0`.
- Some older Uno bootloaders need `-b 57600` instead of `115200`.

## Run

Once the upload finishes, the board resets and runs the new firmware immediately —
no separate "run" step. Observe the onboard LED (or your wired circuit) to verify
behavior against the exercise's "Done when" checklist.

## Exercises

| Folder | Level | Description |
|---|---|---|
| `level1_raw_blink/` | 1 | Blink the onboard LED via direct `DDRB`/`PORTB` register writes |
