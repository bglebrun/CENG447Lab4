#include "state.h"

STATE createDefaultState()
{
    STATE out;
    out.type = MSG_INIT;
    out.pin = PIN_NONE;
    out.setState = NONE;
    out.readState = NONE;
    out.inv = INVALID_NONE;
    out.buffend = 0;
    return out;
}

void setBuffers(STATE state)
{
    state.combuff = strtok(state.iobuff, " ");
    state.pinbuff = strtok(NULL, " ");
    state.setbuff = strtok(NULL, " ");
}

void setMessageType(STATE state)
{
    if (!memcmp("write", state.combuff, 3) ||
        !memcmp("WRITE", state.combuff, 3))
    {
        state.type = MSG_SET;
    }
    else if (!memcmp("read", state.combuff, 4) ||
             !memcmp("READ", state.combuff, 4))
    {
        state.type = MSG_READ;
    }
    else
    {
        state.inv = INVALID_COMMAND;
        state.type = MSG_INV;
    }
}

void setPinNumber(STATE state)
{

    state.inv = INVALID_PIN;
    state.pin = PIN_NONE;
    int input = atoi(state.pinbuff);
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

void setPinMode(STATE state)
{
    if (!memcmp("high", state.setbuff, 4) || !memcmp("HIGH", state.setbuff, 4))
    {
        state.setState = HIGH;
    }
    else if (!memcmp("low", state.setbuff, 3) ||
             !memcmp("LOW", state.setbuff, 3))
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
