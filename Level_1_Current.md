# Level 1 — Foundations: Current Milestone

Status: **In progress**

## Milestone

Blink an LED with a controllable rate, where the blink speed changes based on a push-button press, all programmed by writing directly to hardware registers (no `digitalWrite()`, no HAL abstraction layers).

This proves you can: read a datasheet, configure GPIO as both output and input at the register level, and structure a basic control loop in C.

## Hands-on Exercise

**Setup**
1. Pick a board you have or can get cheaply: Arduino Uno (ATmega328P), STM32 Nucleo, or ESP32 all work. Note which one you're using since register names will differ.
2. Install a toolchain that lets you write raw C without the Arduino abstraction layer (e.g., avr-gcc + avrdude for AVR boards, or STM32CubeIDE/PlatformIO in "bare metal" mode for STM32/ESP32).
3. Find and skim your chip's datasheet section on GPIO configuration registers (e.g., DDRx/PORTx/PINx for AVR, GPIOx_MODER/ODR/IDR for STM32).

**Build**
1. Configure one GPIO pin as output (connect an LED + resistor, or use the onboard LED).
2. Configure a second GPIO pin as input (connect a push button with a pull-up or pull-down resistor).
3. Write C code that toggles the output pin on a delay loop, blinking the LED — using direct register writes, not library functions.
4. Read the button's input register in your loop. Each time the button is pressed, change the blink delay (e.g., cycle through slow/medium/fast).
5. Add basic debounce logic (a short delay check is fine at this level).

**Done when:**
- Code flashes and runs on real hardware.
- LED blinks continuously.
- Pressing the button visibly changes the blink rate.
- You can point to the exact register writes in your code and explain what each one does.

---

Tell me when this is done and I'll review before we move to Level 2.
