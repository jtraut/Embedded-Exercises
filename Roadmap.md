# Embedded Software/Firmware Engineering — Mastery Roadmap

Five levels, beginner to advanced. Do not advance to the next level until the current milestone is confirmed complete.

---

## Level 1: Foundations

**Covers:** C fundamentals (pointers, structs, bitwise ops), number systems (binary/hex), basic electronics (voltage, current, digital logic), microcontroller architecture basics, GPIO, reading a datasheet, flashing firmware to a board.

**Mastery looks like:** You can read a microcontroller datasheet and locate register definitions. You can write C that manipulates hardware registers directly (not just calling library functions). You can explain the difference between a microcontroller and a microprocessor, and between digital and analog signals. You can build, flash, and debug a simple program on real hardware without hand-holding.

---

## Level 2: Core Embedded Skills

**Covers:** Timers, interrupts and ISRs, PWM, ADC/DAC, communication protocols (UART, SPI, I2C), memory-mapped I/O, register-level peripheral configuration, intro to RTOS concepts, using a logic analyzer/oscilloscope.

**Mastery looks like:** You can write interrupt-driven code and reason about ISR safety (race conditions, volatile, atomicity). You can wire up and program I2C/SPI communication with an external peripheral (sensor, EEPROM, display) using raw registers. You can capture and interpret a signal on a logic analyzer to debug a protocol issue.

---

## Level 3: Intermediate Systems

**Covers:** RTOS (e.g., FreeRTOS) — tasks, scheduling, semaphores, mutexes, queues; memory management (stack vs. heap, fragmentation); bootloaders; CAN/USB basics; power management and low-power modes.

**Mastery looks like:** You can design a multi-tasking firmware application with an RTOS and correctly reason about concurrency (deadlocks, priority inversion). You can write a basic bootloader that can flash new application firmware. You can profile and reduce power consumption using sleep/low-power modes.

---

## Level 4: Advanced Firmware Engineering

**Covers:** Board bring-up from schematic/datasheet, custom driver development, DMA, real-time constraints and timing analysis, MISRA-C or similar coding standards, unit testing and hardware-in-the-loop (HIL) testing, firmware version control workflows, basic security (secure boot, firmware signing).

**Mastery looks like:** You can bring up a new, undocumented-to-you board from a schematic and datasheet alone. You can write a hardware driver from scratch given only a peripheral datasheet. You can set up automated unit tests for firmware logic and a HIL test rig for hardware-dependent behavior. You write code that would pass a MISRA-C style review.

---

## Level 5: Expert / Systems Architecture

**Covers:** Firmware architecture design for large systems, multi-core/multi-processor coordination, wireless stacks (BLE/Zigbee/LoRa), OTA update systems, functional safety standards (ISO 26262, IEC 61508), systems-level performance profiling and optimization, technical leadership.

**Mastery looks like:** You can architect a complex embedded system end-to-end (hardware/firmware boundary, update strategy, safety case) and defend the tradeoffs. You can design and implement a secure OTA update pipeline. You can lead a firmware team through a safety-critical certification process and mentor engineers through Levels 1–4.

---

## Current Level

**Active: Level 1** — see `Level_1_Current.md` for the active milestone and exercise.
