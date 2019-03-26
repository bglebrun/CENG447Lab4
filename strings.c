#include "strings.h"

void printMsg(FILE* out, STATE* state)
{
    if (state->type == MSG_INV)
    {
        fprintf(out, uiMsgs[state->type], errorMsgs[state->inv]);
    }
    else if (state->type == MSG_SET)
    {
        fprintf(out, uiMsgs[state->type], pinMsgs[state->pin],
                stateMsgs[state->setState]);
    }
    else if (state->type == MSG_READ)
    {
        fprintf(out, uiMsgs[state->type], pinMsgs[state->pin],
                stateMsgs[state->readState]);
    }
    else if (state->type == MSG_INIT)
    {
        fprintf(out, commands);
        fprintf(out, pins);
        fprintf(out, additionalNotes);
    }
}
