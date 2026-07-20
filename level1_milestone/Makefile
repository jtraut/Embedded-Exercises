MCU     = atmega328p
F_CPU   = 16000000UL
PORT    ?= COM4
BAUD    = 115200

CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

SRC     = $(wildcard *.c)
TARGET  = $(basename $(SRC))
ELF     = $(TARGET).elf
HEX     = $(TARGET).hex

.PHONY: all flash run clean

all: $(HEX)

$(ELF): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash run: $(HEX)
	$(AVRDUDE) -C "$(AVRDUDE_CONF)" -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$(HEX):i

clean:
	rm -f $(ELF) $(HEX)
