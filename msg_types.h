#ifndef _MSG_TYPES_H_
#define _MSG_TYPES_H_
/* ENUM TYPES */
enum MSG_TYPE
{
    MSG_INV = 0,
    MSG_SET,
    MSG_READ
};

enum TGT_PIN
{
    PIN_EIGHT = 0,
    PIN_NINE,
    PIN_TEN,
    PIN_ELEVEN
};

enum SET_TYPE
{
    LOW = 0,
    HIGH
};

enum INVALID_TYPE
{
    INVALID_STATE = 0,
    INVALID_PIN,
    INVALID_COMMAND,
    INVALID_NONE
};
#endif
