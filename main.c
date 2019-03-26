#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include "avr/interrupt.h"
#include "avr/io.h"
#include "pinops.h"
#include "state.h"
#include "stdio.h"
#include "string.h"
#include "strings.h"
#include "util/delay.h"

/* FUNCTION PROTOTYPES */
static int uart_putchar(char c, FILE* stream);
void initUART();

/* Program State */
static STATE state;

/* stdout stream */
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

// program entry point, runs initialization routines.
int main(void)
{
    initUART();
    initPins();
    state = createDefaultState();
    // set global interrupts
    sei();
    fprintf(&mystdout, initialMsg[0]);
    fprintf(&mystdout, initialMsg[1]);
    fprintf(&mystdout, initialMsg[2]);
    while (1)
    {
    }
    return 1;
}

void processMessage(char iobuff[])
{
    state.combuff = strtok(iobuff, " ");
    state.pinbuff = strtok(NULL, " ");
    state.setbuff = strtok(NULL, " ");
    if (state.combuff == NULL)
    {
        state.type = MSG_INV;
        state.inv = INVALID_COMMAND;
    }
    else
    {
        // these functions change global state
        // based on the input buffer
        setMessageType(state.combuff, state);
        setPinNumber(state.pinbuff, state);
        switch (state.type)
        {
        case MSG_READ:
            setReadState(ReadPinDigital(state.pin), state);
            break;
        case MSG_SET:
            setPinMode(state.setbuff, state);
            if (state.type != MSG_INV)
                WritePinDigital(state.pin, state.setState);
            break;
        case MSG_INV:
            break;
        }
    }

    printMsg(&mystdout, state);
}

ISR(USART_RX_vect)
{
    char inByte = UDR0;

    // processing goes here
    if (inByte == '\r')
    {
        state.buffend = 0;
        // process string here
        processMessage(state.iobuff);
        // clear io buffer when done
        memset(state.iobuff, 0, 32 * sizeof(char));
    }
    else
    {
        // continue to write to a fifo buffer
        state.iobuff[state.buffend++] = inByte;
        inByte = 0;
        // check if the buffer is at capacity
        // (shouldn't ever happen under) normal circumstances
        if (state.buffend == 31)
        {
            // print buffer overflow error msg.
            fprintf(&mystdout, overflowMsg);
            // set index back to 0
            state.buffend = 0;
            // clear the buffer
            memset(state.iobuff, 0, 32 * sizeof(char));
        }
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

static int uart_putchar(char c, FILE* stream)
{
    if (c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}
