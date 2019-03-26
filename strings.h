#ifndef _STRINGS_H_
#define _STRINGS_H_
#include "state.h"
#include "stdio.h"

// ui msgs
static const char invalidMsg[] =
    "%s, Command structure: ' READ/ (WRITE) PIN_NUM (HIGH|LOW)'\r\n";
static const char setPin[] = "Pin %s set %s\r\n";
static const char readPin[] = "Pin %s reads %s\r\n";
// state msgs
static const char lowMsg[] = "LOW";
static const char highMsg[] = "HIGH";
static const char noneMsg[] = "NONE";
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

// initial msgs
static const char commands[] = "Available commands are: WRITE, READ\r\n"
                               "Instruction formats:\r\n"
                               "WRITE: WRITE (out_pin) (HIGH|LOW)\r\n"
                               "sets 'out_pin' high or low\r\n"
                               "READ: READ (in_pin)\r\n"
                               "reads the state of 'in_pin'\r\n";
static const char pins[] = "Valid pins:\r\n"
                           "in_pin: 9, 11\r\n"
                           "these pins may be used with the READ command\r\n"
                           "out_pin: 8, 10\r\n"
                           "these pins may be used with the WRITE command\r\n";
static const char additionalNotes[] =
    " Additional notes:\r\n"
    "- commands and set states may be all-uppercase or all-lowercase, but not "
    "mixed\r\n"
    "- commands are expected to be space separated, and input is processed on "
    "newline input\r\n";

// overflow msg
static const char overflowMsg[] = "ERROR: input over max length (31 characters "
                                  "+ carriage return). clearing buffer.";

// msg lists
static const char* uiMsgs[] = {invalidMsg, setPin, readPin};
static const char* stateMsgs[] = {lowMsg, highMsg, noneMsg};
static const char* pinMsgs[] = {pinEight, pinNine, pinTen, pinEleven, pinNone};
static const char* errorMsgs[] = {invalidState, invalidPin, invalidCommand,
                                  invalidNone};
static const char* initialMsg[] = {commands, pins, additionalNotes};

// prototype for printMsg
void printMsg(FILE* out, STATE state);

#endif
