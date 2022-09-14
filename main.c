#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define MOTION_DETECTED (PINA & (1 << PA0))

volatile uint8_t timer;

void yellow_led_on() {
    PORTC |= (1 << PC0);
}

void yellow_led_off() {
    PORTC &= !(1 << PC0);
}

void green_led_on() {
    PORTC |= (1 << PC1);
}

void green_led_off() {
    PORTC &= !(1 << PC1);
}

ISR(INT0_vect) {
    yellow_led_on();
}

// ISR(INT1_vect) {
//     led_on();
//     _delay_ms(1000);
// }

ISR(TIMER0_COMP_vect) {
    timer++;
}

int main(void) {
    DDRC |= 0xFF;
    DDRA |= 0;

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
    // Turn on interrupts on pin INT1
    // GICR |= (1 << INT1);

    // Generate INT1 interrupt on rising egde
    // MCUCR |= (1 << ISC11) | (1 << ISC10);

    sei();
    _delay_ms(2000);
    while (1) {
        if (timer == 0) {
            yellow_led_on();
            _delay_ms(100);
        } else {
            yellow_led_off();
        }
        if (MOTION_DETECTED) {
            green_led_on();
        } else {
            green_led_off();
        }
        yellow_led_off();
    }
    return 0;
}