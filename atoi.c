#include "atoi.h"

// convert a null terminated string containing
// the ascii representation of a number to its
// integer representation
int atoi(char* c)
{
    int result = 0;

    for (int i = 0; c[i] != '\0'; i++)
    {
        result = result * 10 + (c[i] - 0x30);
    }

    return result;
}
