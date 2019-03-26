#include "strings.h"

void printMsg(FILE* out, STATE state)
{
    const char* str = uiMsgs[state.type];
    if (state.type == MSG_INV)
    {
        fprintf(out, str, errorMsgs[state.inv]);
    }
    else if (state.type == MSG_SET)
    {
        fprintf(out, str, pinMsgs[state.pin], stateMsgs[state.setState]);
    }
    else
    {
        fprintf(out, str, pinMsgs[state.pin], stateMsgs[state.readState]);
    }
}
