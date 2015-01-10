#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t activeLed = 1;
uint8_t direction = 0;

void larsson_latch();

uint8_t lastPressedState = 0;

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

    //Set output for block B
    DDRB = 255;

    //set F0 input
    PORTF = (1 << PF0);

    // set LED pin to output
        clock_prescale_set(clock_div_1);
    // enable interrupts globally
    sei();
    while (1)
    {}
}

void larsson_latch()
{
    for (uint8_t i = 0; i < 16; i++)
    {
        if ((activeLed >> i)  & 0x01)
        {
            PORTB |= (1 << PB0);
        }
        else
        {
            PORTB &= ~(1 << PB0);
        }

        PORTB |= (1 << PB1);
        PORTB &= ~(1 << PB1);
    }
    PORTB |= (1 << PB2);
    PORTB &= ~(1 << PB2);

    if (direction == 0)
    {
        activeLed <<= 1;
    }
    else
    {
        activeLed >>= 1;
    }

    if (activeLed == 0x8000)
    {
        direction = 1;
    }
    if (activeLed == 1)
    {
        direction = 0;
    }
}

ISR(TIMER1_COMPA_vect)
{
    larsson_latch();
}
