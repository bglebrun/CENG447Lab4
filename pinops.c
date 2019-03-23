#include "pinops.h"

/*
 * Sets pins into correct modes
 * 8   - out(1)
 * 9   - in (0)
 * 10  - out(1)
 * 11  - in (0)
 */
void initPins() {
    DDRB = 0x05;
    return;
}

/*
 * Reads current status of target pin
 * returns 0 if no signal, returns -1
 * for invalid pin, otherwise non zero
 * numbers indicate pin is set
 * 
 * RETURNS:
 * -1 - Invalid pin
 * 0 - Pin not set
 * Else - Pin set
 */
int ReadPinDigital(enum TGT_PIN pin) {
    switch(pin){
        case PIN_TEN:
            return PINB & 0x04;
        break;
        case PIN_EIGHT:
            return PINB & 0x01;
        break;
        default:
        return -1;
    }
    return -1;
}

/*
 * Sets target pin to target mode,
 * If invalid pin will return 1, 
 * otherwise should return 0
 * 
 * RETURNS:
 * 1 - Pin not set
 * 0 - Pin was set
 */
int WritePinDigital(enum TGT_PIN pin, enum SET_TYPE mode) {
    switch(pin){
        case PIN_NINE:
            switch(mode){
                case HIGH:
                    PORTB |= 0x02;
                break;
                case LOW:
                    PORTB &= 0xFD;
                break;
                default:
                    return 1;
            }
        break;
        case PIN_ELEVEN:
            switch(mode){
                case HIGH:
                    PORTB |= 0x08;
                break;
                case LOW:
                    PORTB &= 0x7B;
                break;
                default:
                    return 1;
            }
        break;
        default:
        return 1;
    }

    return 0;
}