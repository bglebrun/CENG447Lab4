#ifndef _PINOPS_H_
#define _PINOPS_H_
#include "msgtypes.h"
#include <avr/io.h>
void initPins();
int ReadPinDigital(enum TGT_PIN pin);
int WritePin(enum TGT_PIN pin, enum SET_TYPE mode);
#endif