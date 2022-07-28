#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define KEY_PRESSED !(PINC & (1 << PC0))

int main(void) {
    DDRD |= 0xFF;
    // DDRC |= (1 << PC1);
    while (1) {
        if (KEY_PRESSED) {
            PORTD = 0xFF;
            // PORTC |= (1 << PC1);
        } else {
            PORTD = 0x00;
            // PORTC &= !(1 << PC1);
        }
    }
    return 0;
}