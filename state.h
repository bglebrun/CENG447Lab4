#ifndef _STATE_H_
#define _STATE_H_
#include "atoi.h"
#include "enums.h"
/* State struct, contains the global state of the program*/
typedef struct STATE
{
    // state flags
    enum MSG_TYPE type;
    enum TGT_PIN pin;
    enum SET_TYPE setState;
    enum SET_TYPE readState;
    enum INVALID_TYPE inv;

    // input buffer
    char iobuff[32];
    char* combuff;
    char* pinbuff;
    char* setbuff;
    int buffend; // tracks end of iobuff
} STATE;

/* STATE object constructor */
STATE createDefaultState();

/* State manipulation functions*/
void setMessageType(char* str, STATE state);
void setPinNumber(char* str, STATE state);
void setPinMode(char* str, STATE state);
void setReadState(int pinStatus, STATE state);

#endif
