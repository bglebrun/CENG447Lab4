#ifndef _STRINGS_H_
#define _STRINGS_H_
#include "msg_types.h"

static const char* uiMsgs[] = {invalidMsg, setPin, readPin};
static const char* stateMsgs[] = {lowMsg, highMsg};
static const char* pinMsgs[] = {pin_eight, pin_nine, pin_ten, pin_eleven};
// ui msgs
static const char invalidMsg[] =
    "INVALID PIN, Command structure: ' READ/ (WRITE) PIN_NUM (HIGH|LOW)'";
static const char setPin[] = "Pin %s set %s";
static const char readPin[] = "Pin %s reads %s";
// state msgs
static const char lowMsg[] = "LOW";
static const char highMsg[] = "HIGH";
// pin msgs
static const char pin_eight[] = "eight";
static const char pin_nine[] = "nine";
static const char pin_ten[] = "ten";
static const char pin_eleven[] = "eleven";

#endif
