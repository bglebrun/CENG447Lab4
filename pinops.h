#ifndef _PINOPS_H_
#define _PINOPS_H_
#include "msg_types.h"
void initPins();
int ReadPinDigital(TGT_PIN pin);
int WritePin(TGT_PIN pin, SET_TYPE mode);
#endif