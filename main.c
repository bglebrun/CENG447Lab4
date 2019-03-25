#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include "avr/interrupt.h"
#include "avr/io.h"
#include "msg_types.h"
#include "pinops.h"
#include "stdio.h"
#include "string.h"
#include "strings.h"
#include "util/delay.h"

/* FUNCTION PROTOTYPES */
static int uart_putchar(char c, FILE* stream);
uint8_t uart_getchar(void);
void initUART();
void printMsg();

/* GLOBAL CONST */
char iobuff[32];
int i = 0; // tracks end of iobuff
int j = 0; // tracks end of consumed input
enum MSG_TYPE type = MSG_INV;
enum TGT_PIN pin = PIN_EIGHT;
enum SET_TYPE set = LOW;
enum INVALID_TYPE inv = INVALID_COMMAND;

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

int main(void)
{
    initUART();
    initPins();
    // stdout = &mystdout;
    // stdin = &mystdin;
    // set global interrupts
    sei();
    while (1)
    {
        printMsg();
        while (1)
        {
        }
    }
    return 1;
}

void setMessageType(char iobuff[])
{
    if (!memcmp("set", iobuff, 3) || !memcmp("SET", iobuff, 3))
    {
        type = MSG_SET;
        j = 5;
    }
    else if (!memcmp("read", iobuff, 4) || !memcmp("READ", iobuff, 4))
    {
        type = MSG_READ;
        j = 6;
    }
    else
    {
        inv = INVALID_COMMAND;
        type = MSG_INV;
    }
}

void setPinNumber(char iobuff[], enum MSG_TYPE mode)
{
    char num[3];
    inv = INVALID_PIN;
    switch (mode)
    {
    case MSG_READ:
        memcpy(num, &iobuff[6], 3);
        if (!memcmp("8", num, 1))
        {
            pin = PIN_EIGHT;
            inv = INVALID_NONE;
        }
        else if (!memcmp("10", num, 2))
        {
            pin = PIN_TEN;
            inv = INVALID_NONE;
        }
        break;
    case MSG_SET:
        memcpy(num, &iobuff[5], 3);
        if (!memcmp("9", num, 1))
        {
            pin = PIN_NINE;
            inv = INVALID_NONE;
        }
        else if (!memcmp("10", num, 2))
        {
            pin = PIN_TEN;
            inv = INVALID_NONE;
        }
        break;
    case MSG_INV:
        break;
    }

    if (inv == INVALID_PIN)
    {
        type = MSG_INV;
    }

    j += 3;
}

void setPinMode(char iobuff[])
{
    char tmp[5];
    memcpy(tmp, &iobuff[j], 5);

    if (!memcmp("high", tmp, 4) || !memcmp("HIGH", tmp, 4))
    {
        set = HIGH;
    }
    else if (!memcmp("low", tmp, 3) || !memcmp("LOW", tmp, 3))
    {
        set = LOW;
    }
    else
    {
        /*ERROR*/
        type = MSG_INV;
        inv = INVALID_STATE;
    }
}

void processMessage(char iobuff[])
{
    // these functions change global state
    // based on the input buffer
    setMessageType(iobuff);
    setPinNumber(iobuff, type);
    int pinStatus = 0;
    switch (type)
    {
    case MSG_READ:
        // TODO: this is clunky and error prone,
        // there should be another enum/variable to store this
        // status
        pinStatus = ReadPinDigital(pin);
        if (pinStatus == 0)
        {
            set = LOW;
        }
        else if (pinStatus == 1)
        {
            set = HIGH;
        }
        break;
    case MSG_SET:
        setPinMode(iobuff);
        if (type != MSG_INV)
            WritePinDigital(pin, set);
        break;
    case MSG_INV:
        break;
    }
    printMsg();
}

ISR(USART_RX_vect)
{
    char inByte = UDR0;

    // processing goes here
    if (inByte == '\r')
    {
        i = 0;
        // process string here
        processMessage(iobuff);
        // clear io buffer when done
        memset(iobuff, 0, sizeof iobuff);
    }
    else
    {
        // continue to write to a fifo buffer
        iobuff[i++] = inByte;
        inByte = 0;
    }
}

void initUART()
{
    // init uart
    UCSR0B |= 0x98;
    UCSR0C |= 0x06;
    UBRR0L = BAUD_PRESCALE;
    UBRR0H = (BAUD_PRESCALE >> 8);
}

void printMsg()
{
    const char* str = uiMsgs[type];
    if (type == MSG_INV)
    {
        fprintf(&mystdout, str, errorMsgs[inv]);
    }
    else
    {
        fprintf(&mystdout, str, pinMsgs[pin], stateMsgs[set]);
    }
}

static int uart_putchar(char c, FILE* stream)
{
    if (c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}

uint8_t uart_getchar(void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }
    return (UDR0);
}
