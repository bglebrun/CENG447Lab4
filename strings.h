#ifndef _STRINGS_H_
#define _STRINGS_H_

// ui msgs
static const char invalidMsg[] =
    "%s, Command structure: ' READ/ (WRITE) PIN_NUM (HIGH|LOW)'\r\n";
static const char setPin[] = "Pin %s set %s\r\n";
static const char readPin[] = "Pin %s reads %s\r\n";
// state msgs
static const char lowMsg[] = "LOW";
static const char highMsg[] = "HIGH";
// pin msgs
static const char pinEight[] = "eight";
static const char pinNine[] = "nine";
static const char pinTen[] = "ten";
static const char pinEleven[] = "eleven";
static const char pinNone[] = "none";
// invalid types
static const char invalidState[] = "INVALID STATE";
static const char invalidPin[] = "INVALID PIN";
static const char invalidCommand[] = "INVALID COMMAND";
static const char invalidNone[] = "";
// msg lists
static const char* uiMsgs[] = {invalidMsg, setPin, readPin};
static const char* stateMsgs[] = {lowMsg, highMsg};
static const char* pinMsgs[] = {pinEight, pinNine, pinTen, pinEleven, pinNone};
static const char* errorMsgs[] = {invalidState, invalidPin, invalidCommand,
                                  invalidNone};

#endif
