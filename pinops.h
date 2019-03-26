#ifndef _PINOPS_H_
#define _PINOPS_H_
#include "state.h"
#include <avr/io.h>
void initPins();
int ReadPinDigital(enum TGT_PIN pin);
int WritePinDigital(enum TGT_PIN pin, enum SET_TYPE mode);
#endif
