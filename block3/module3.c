#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
# include <avr/io.h>
#include <avr/interrupt.h>

uint8_t activeLed = 1;
uint8_t direction = 0;

int main(void)
{
    // setup for timer
    TCCR1A = 0;
    TCCR1C = 0;
    TCNT1  = 0;
    OCR1A  = 3906;
    TIMSK1 = 1 << OCIE1A;
    TIFR1  = 0xFF;
    // Set TCCR1B last because setting CS starts the T/C
    TCCR1B = (1 << WGM12) | (5 << CS10);

    DDRB = 255;

    // set LED pin to output
        clock_prescale_set(clock_div_1);
    // enable interrupts globally
    sei();
    while (1) {}
}

ISR(TIMER1_COMPA_vect)
{
    PORTB = activeLed;

    if (direction == 0)
    {
        activeLed <<= 1;
    }
    else
    {
        activeLed >>= 1;
    }

    if (activeLed == 128)
    {
        direction = 1;
    }
    if (activeLed == 1)
    {
        direction = 0;
    }

}
