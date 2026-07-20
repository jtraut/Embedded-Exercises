#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* PB5 = Arduino digital pin 13 = onboard LED. Set as output.
     *
     * (1 << PB5)   "1" is 0b00000001. PB5 is just the number 5 (defined by
     *              avr/io.h), so this shifts the 1 left by 5 places,
     *              producing 0b00100000 -- a "mask" with only bit 5 set.
     *              This is how you build a mask for "one specific pin"
     *              without hardcoding the binary by hand.
     *
     * DDRB |= ...  DDRB (Data Direction Register B) has one bit per pin on
     *              port B; 1 = output, 0 = input. |= is "read DDRB, OR it
     *              with the mask, write it back". OR-ing with a mask that
     *              has only bit 5 set FORCES bit 5 to 1 while leaving every
     *              other bit in DDRB untouched (X | 0 == X, X | 1 == 1).
     *              This is the standard idiom for "set one bit without
     *              disturbing the rest of the register".
     */
    DDRB |= (1 << PB5);

    while (1) {
        /* PORTB ^= (1 << PB5);
         *
         * XOR-toggling a bit: for any bit b, b ^ 1 flips it (0^1=1, 1^1=0),
         * while b ^ 0 leaves it alone (0^0=0, 1^0=1). Since our mask is 0
         * everywhere except bit 5, XOR-ing PORTB with it flips ONLY bit 5
         * (the LED's on/off state) and leaves every other pin in PORTB
         * exactly as it was. That's why toggling uses ^= but setting an
         * output direction above used |= -- OR can only ever turn bits on,
         * XOR can flip a bit whichever way it currently isn't.
         */
        PORTB ^= (1 << PB5);   /* toggle LED */
        _delay_ms(2500);          /* wait 2.5 seconds */
    }
}
