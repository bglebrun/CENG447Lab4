#ifndef _MSG_TYPES_H_
#define _MSG_TYPES_H_
/* ENUM TYPES */
enum MSG_TYPE
{
    MSG_NONE = 0,
    MSG_SET,
    MSG_READ,
    MSG_INV
};

enum TGT_PIN
{
    PIN_EIGHT,
    PIN_NINE,
    PIN_TEN,
    PIN_ELEVEN,
};

enum SET_TYPE
{
    LOW,
    HIGH
};
#endif