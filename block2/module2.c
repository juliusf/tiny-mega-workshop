#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
# include <avr/io.h>
#include <avr/interrupt.h>
int main(void)
{
    // setup for timer
    TCCR1A = 0;
    TCCR1C = 0;
    TCNT1  = 0;
    OCR1A  = 7812;
    TIMSK1 = 1 << OCIE1A;
    TIFR1  = 0xFF;
    // Set TCCR1B last because setting CS starts the T/C
    TCCR1B = (1 << WGM12) | (5 << CS10);

    // set LED pin to output
    DDRE = (1 << PE6);
    clock_prescale_set(clock_div_1);
    // enable interrupts globally
    sei();
    while (1) {}
}

ISR(TIMER1_COMPA_vect)
{
    if (!(PINE & _BV(PE6)))
    {
       PORTE = (1 << PE6);
    }else
    {
        PORTE = (0 << PE6);
    }
}
