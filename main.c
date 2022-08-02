#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t timer;

ISR(INT0_vect) {
    PORTC |= (1 << PC0);
}

ISR(TIMER0_COMP_vect) {
    timer++;
}

int main(void) {
    DDRC |= 0xFF;

    // CTC mode for Timer0
    TCCR0 |= (1 << WGM01);
    // 64 timer divider
    TCCR0 |= (1 << CS00) | (1 << CS01);
    // Timer's top value 
    OCR0 = 255;
    // Turn on the Timer/Counter0 Compare Match interrupt
    TIMSK |= (1 << OCIE0);

    // Turn on interrupts on pin INT0
    GICR |= (1 << INT0);

    sei();
    while (1) {
        if (timer == 0) {
            PORTC |= (1 << PC0);
            _delay_ms(100);
        } else {
            PORTC &= !(1 << PC0);
        }
    }
    return 0;
}