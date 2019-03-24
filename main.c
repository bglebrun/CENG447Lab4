#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include "msg_types.h"
#include "pinops.h"
#include "strings.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

/* FUNCTION PROTOTYPES */
static int uart_putchar(char c, FILE* stream);
uint8_t uart_getchar(void);
void initUART();
void printMsg();

/* GLOBAL CONST */
char iobuff[32];
int i = 0;
enum MSG_TYPE type = MSG_INV;
enum TGT_PIN pin = PIN_EIGHT;
enum SET_TYPE set = LOW;

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

int main(void)
{
    initUART();
    initPins();
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

enum MSG_TYPE getMessageType(char iobuff[]) {
    if(!memcmp("set", iobuff, 3) || !memcmp("SET", iobuff, 3)) {
        return MSG_SET; 
    } else if(!memcmp("read", iobuff, 4) || !memcmp("READ", iobuff, 3)){
        return MSG_READ;
    } else return MSG_INV;
}

enum TGT_PIN getPinNumber(char iobuff[], enum MSG_TYPE mode) {
    char num[3];
    switch(mode) {
        case MSG_READ:
            memcpy(num, iobuff[6], 3);
            if(!memcmp('8', num, 1)) return PIN_EIGHT;
            else if (!memcmp("10", num, 2)) return PIN_TEN;
        break;
        case MSG_SET:
            memcpy(num, iobuff[5], 3);
            if(!memcmp('9', num, 1)) return PIN_NINE;
            else if (!memcmp("10", num, 2)) return PIN_TEN;
        break;
    }
    return 0;
}

void processMessage(char iobuff[]) {
    type = getMessageType(iobuff);
    pin = getPinNumber(iobuff, type);
    if (type == MSG_SET) {

    }
    int pinStatus = 0;
    switch (type) {
        case MSG_READ:
            
        break; 
        case MSG_SET:

        break;
        case MSG_INV:

        break;
    }
}

ISR(USART_RX_vect)
{
    char inByte = UDR0;
    // processing goes here
    if (inByte == '\n')
    {
        i = 0;
        // process string here

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
        fprintf(&mystdout, str);
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
