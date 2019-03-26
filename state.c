#include "state.h"

STATE createDefaultState()
{
    STATE out;
    out.type = MSG_INV;
    out.pin = PIN_NONE;
    out.setState = NONE;
    out.readState = NONE;
    out.inv = INVALID_NONE;
    out.buffend = 0;
    return out;
}

void setMessageType(char* str, STATE state)
{
    if (!memcmp("write", str, 3) || !memcmp("WRITE", str, 3))
    {
        state.type = MSG_SET;
    }
    else if (!memcmp("read", str, 4) || !memcmp("READ", str, 4))
    {
        state.type = MSG_READ;
    }
    else
    {
        state.inv = INVALID_COMMAND;
        state.type = MSG_INV;
    }
}

void setPinNumber(char* str, STATE state)
{
    state.inv = INVALID_PIN;
    state.pin = PIN_NONE;
    int input = atoi(str);
    switch (state.type)
    {
    case MSG_SET:
        if (input == 8)
        {
            state.pin = PIN_EIGHT;
            state.inv = INVALID_NONE;
        }
        else if (input == 10)
        {
            state.pin = PIN_TEN;
            state.inv = INVALID_NONE;
        }
        break;
    case MSG_READ:
        if (input == 9)
        {
            state.pin = PIN_NINE;
            state.inv = INVALID_NONE;
        }
        else if (input == 11)
        {
            state.pin = PIN_ELEVEN;
            state.inv = INVALID_NONE;
        }
        break;
    case MSG_INV:
        break;
    }

    if (state.inv == INVALID_PIN)
    {
        state.type = MSG_INV;
    }
}

void setPinMode(char* str, STATE state)
{
    if (!memcmp("high", str, 4) || !memcmp("HIGH", str, 4))
    {
        state.setState = HIGH;
    }
    else if (!memcmp("low", str, 3) || !memcmp("LOW", str, 3))
    {
        state.setState = LOW;
    }
    else
    {
        /*ERROR*/
        state.type = MSG_INV;
        state.inv = INVALID_STATE;
    }
}

void setReadState(int pinStatus, STATE state)
{
    if (pinStatus == 0)
    {
        state.readState = LOW;
    }
    else if (pinStatus == 1)
    {
        state.readState = HIGH;
    }
    else
    {
        state.readState = NONE;
    }
}
