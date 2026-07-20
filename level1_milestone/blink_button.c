#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN     PB5   /* Arduino pin 13 (onboard LED) */
#define BUTTON_PIN  PD2   /* Arduino pin 2 */

int main(void)
{
    /* LED pin as output */
    DDRB |= (1 << LED_PIN);

    /* Button pin as input, internal pull-up enabled (idle = HIGH, pressed = LOW) */
    DDRD  &= ~(1 << BUTTON_PIN);
    PORTD |=  (1 << BUTTON_PIN);

    const uint16_t speeds_ms[] = {1000, 300, 100};   /* slow, medium, fast */
    uint8_t speed_index = 0;
    uint8_t button_was_pressed = 0;

    while (1) {
        uint8_t button_is_pressed = !(PIND & (1 << BUTTON_PIN));

        if (button_is_pressed && !button_was_pressed) {
            _delay_ms(30);                              /* debounce settle */
            if (!(PIND & (1 << BUTTON_PIN))) {           /* still pressed? */
                speed_index = (speed_index + 1) % 3;     /* cycle speed */
            }
        }
        button_was_pressed = button_is_pressed;

        PORTB ^= (1 << LED_PIN);                         /* toggle LED */

        /* busy-wait for the current speed setting, in 10ms steps */
        for (uint16_t i = 0; i < speeds_ms[speed_index] / 10; i++) {
            _delay_ms(10);
        }
    }
}
