#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN     PB5   /* Arduino pin 13 (onboard LED); PB5 = bit 5 of Port B */
#define BUTTON_PIN  PD2   /* Arduino pin 2; PD2 = bit 2 of Port D, also INT0 (external interrupt 0) */

int main(void)
{
    /* LED pin as output. See blink.c for the full breakdown of (1 << PIN)
     * as a "single bit mask" and |= as "set this one bit, leave the rest". */
    DDRB |= (1 << LED_PIN);

    /* Button pin as input, internal pull-up enabled (idle = HIGH, pressed = LOW)
     *
     * (1 << BUTTON_PIN)   Same masking trick as before: BUTTON_PIN is 2, so
     *                     this is 0b00000100 -- a mask with only bit 2 set.
     *
     * ~(1 << BUTTON_PIN)  ~ is bitwise NOT: it flips every bit. Flipping
     *                     0b00000100 gives 0b11111011 -- every bit set to 1
     *                     EXCEPT bit 2, which is 0. This is the "inverse
     *                     mask", used whenever you want to clear one bit.
     *
     * DDRD &= ~(...)      AND-ing a register with the inverse mask forces
     *                     bit 2 to 0 while leaving every other bit alone
     *                     (X & 1 == X, X & 0 == 0). DDRD bit 2 = 0 means
     *                     "pin PD2 is an input". Contrast with DDRB |= above:
     *                     |= with a normal mask forces a bit to 1 (set),
     *                     &= with an inverted mask forces a bit to 0 (clear).
     *
     * PORTD |= (...)      When a pin is configured as an input, writing 1 to
     *                     its PORTx bit (instead of PORTx as an output level)
     *                     has a special meaning on AVR: it enables that pin's
     *                     internal pull-up resistor. Same "set one bit" |=
     *                     idiom as the DDRB line above, just on a different
     *                     register. With the pull-up on, the pin reads HIGH
     *                     when the button is open, and the button press pulls
     *                     it down to LOW (hence "pressed = LOW" below).
     */
    DDRD  &= ~(1 << BUTTON_PIN);
    PORTD |=  (1 << BUTTON_PIN);

    const uint16_t speeds_ms[] = {1000, 300, 100};   /* slow, medium, fast */
    uint8_t speed_index = 0;
    uint8_t button_was_pressed = 0;
    uint8_t button_is_pressed = 0;

    while (1) {
        /* !(PIND & (1 << BUTTON_PIN))
         *
         * PIND is the register you READ to see the current electrical level
         * on each pin of port D (as opposed to DDRD = direction, PORTD =
         * output value/pull-up config). PIND & mask uses AND to ISOLATE bit
         * 2: every other bit gets AND-ed with 0 and becomes 0, while bit 2
         * survives as whatever it actually was (X & 1 == X). So the result
         * is 0b00000100 if the pin is HIGH, or 0b00000000 if the pin is LOW
         * -- everything else is zeroed out, regardless of what it was.
         *
         * That result is still "0b00000100" (i.e. 4), not "1", when the pin
         * is high -- masking only isolates the bit, it doesn't move it to
         * position 0. The leading ! (logical NOT, not bitwise ~) then
         * collapses that isolated value down to a plain boolean: any nonzero
         * value becomes 0, and zero becomes 1. Since we wired a pull-up
         * (idle = HIGH = pin electrically 1 = "not pressed"), the raw read
         * is backwards from what we want logically, so ! flips it:
         * pin HIGH (idle)    -> PIND & mask is nonzero -> !(...) = 0 = not pressed
         * pin LOW (pressed)  -> PIND & mask is 0        -> !(...) = 1 = pressed
         */
        // uint8_t button_is_pressed = !(PIND & (1 << BUTTON_PIN));

        if (button_is_pressed && !button_was_pressed) {
            _delay_ms(30);                              /* debounce settle */
            if (!(PIND & (1 << BUTTON_PIN))) {           /* still pressed? (same read+mask+NOT as above) */
                speed_index = (speed_index + 1) % 3;     /* cycle speed */
            }
        }
        button_was_pressed = button_is_pressed;

        PORTB ^= (1 << LED_PIN);   /* toggle LED bit via XOR -- see blink.c for why ^= flips one bit */

        /* busy-wait for the current speed setting, in 10ms steps */
        for (uint16_t i = 0; i < speeds_ms[speed_index] / 10; i++) {
            button_is_pressed = !(PIND & (1 << BUTTON_PIN));
            _delay_ms(10);
        }
    }
}
