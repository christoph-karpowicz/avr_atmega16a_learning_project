#ifndef F_CPU
#define F_CPU 1000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>
#include <util/delay.h>
#define MY_PORT PORTD
#define MY_DDR DDRD

int main(void) {
    MY_DDR |= 0xFF;
    while (1) {
        MY_PORT = 0x00;
        _delay_ms(500);
        MY_PORT = 0xFF;
        _delay_ms(500);
    }
    return 0;
}