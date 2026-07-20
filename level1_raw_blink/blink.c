#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* PB5 = Arduino digital pin 13 = onboard LED. Set as output. */
    DDRB |= (1 << PB5);

    while (1) {
        PORTB ^= (1 << PB5);   /* toggle LED */
        _delay_ms(2500);          /* wait 2.5 seconds */
    }
}
