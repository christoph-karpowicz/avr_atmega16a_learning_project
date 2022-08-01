#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect) {
    PORTC |= (1 << PC0);
}

int main(void) {
    DDRC |= 0xFF;
    GICR |= (1 << INT0);
    sei();
    while (1) {
        PORTC &= !(1 << PC0);
    }
    return 0;
}