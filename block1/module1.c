#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

int main(void)
{
    // Setup code goes here
    DDRE = (1 << PE6);
    clock_prescale_set(clock_div_1);
    while (1) {
        PORTE = (1 << PE6);
        _delay_ms(500);
        PORTE = (0 << PE6);
        _delay_ms(500);
    }
}
