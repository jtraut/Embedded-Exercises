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
which bundles avr-gcc/avrdude under `%LOCALAPPDATA%\Arduino15\packages\arduino\tools\`.
To use the shorthand commands (`avr-gcc`, `avr-objcopy`, `avrdude`) from any shell instead of
typing full paths, add the toolchain's `bin` folders to your `PATH` and point `AVRDUDE_CONF`
at `avrdude.conf` — set these once, permanently, at the user level:

```powershell
$gccVersion = (Get-ChildItem "$env:LOCALAPPDATA\Arduino15\packages\arduino\tools\avr-gcc" | Select-Object -First 1).Name
$avrdudeVersion = (Get-ChildItem "$env:LOCALAPPDATA\Arduino15\packages\arduino\tools\avrdude" | Select-Object -First 1).Name

$gccBin = "$env:LOCALAPPDATA\Arduino15\packages\arduino\tools\avr-gcc\$gccVersion\bin"
$avrdudeBin = "$env:LOCALAPPDATA\Arduino15\packages\arduino\tools\avrdude\$avrdudeVersion\bin"
$avrdudeConf = "$env:LOCALAPPDATA\Arduino15\packages\arduino\tools\avrdude\$avrdudeVersion\etc\avrdude.conf"

$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
[Environment]::SetEnvironmentVariable("Path", "$userPath;$gccBin;$avrdudeBin", "User")
[Environment]::SetEnvironmentVariable("AVRDUDE_CONF", $avrdudeConf, "User")
```

Open a new PowerShell window afterward so it picks up the updated user environment. Verify with:

```powershell
Get-Command avr-gcc, avr-objcopy, avrdude
$env:AVRDUDE_CONF
```

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
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o blink.elf blink.c
avr-objcopy -O ihex -R .eeprom blink.elf blink.hex
```

- `-mmcu=atmega328p` targets the Uno's chip.
- `-DF_CPU=16000000UL` defines the CPU clock speed (16 MHz on the Uno), used by `util/delay.h` timing macros.
- `-Os` optimizes for size (typical for embedded targets).
- `avr-objcopy` converts the ELF binary into the Intel HEX format avrdude expects.

## Upload

Find your board's serial port, then flash it:

```sh
avrdude -C "$env:AVRDUDE_CONF" -v -p atmega328p -c arduino -P <PORT> -b 115200 -D -U flash:w:blink.hex:i
```

- `-C "$env:AVRDUDE_CONF"` points avrdude at its config file (set up in Prerequisites above). On
  macOS/Linux, drop this flag and rely on avrdude's built-in default config, or point it at your
  install's `avrdude.conf` directly.
- `-D` disables auto-erase, so only the pages being written are erased.

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
