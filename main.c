#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include "avr/interrupt.h"
#include "avr/io.h"
#include "pinops.h"
#include "state.h"
#include "stdio.h"
#include "strings.h"
#include "util/delay.h"

/* FUNCTION PROTOTYPES */
static int uart_putchar(char c, FILE* stream);
void initUART();

/* Program State */
static STATE globalState;

/* stdout stream */
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

// program entry point, runs initialization routines.
int main(void)
{
    initUART();
    initPins();
    globalState.type = MSG_INIT;
    globalState = createDefaultState();
    // set global interrupts
    sei();
    printMsg(&mystdout, &globalState);
    while (1)
    {
    }
    return 1;
}

void processMessage(STATE* s)
{
    setBuffers(s);
    if (s->combuff == NULL)
    {
        s->type = MSG_INV;
        s->inv = INVALID_COMMAND;
    }
    else
    {
        // these functions change global state
        // based on the input buffer
        setMessageType(s);
        setPinNumber(s);
        switch (s->type)
        {
        case MSG_READ:
            setReadState(ReadPinDigital(s->pin), s);
            break;
        case MSG_SET:
            setPinMode(s);
            if (s->type != MSG_INV)
                WritePinDigital(s->pin, s->setState);
            break;
        case MSG_INV:
        case MSG_INIT:
            break;
        }
    }

    printMsg(&mystdout, s);
}

ISR(USART_RX_vect)
{
    char inByte = UDR0;

    // processing goes here
    if (inByte == '\r')
    {
        globalState.buffend = 0;
        // process string here
        processMessage(&globalState);
        // clear io buffer when done
        memset(globalState.iobuff, 0, 32 * sizeof(char));
    }
    else
    {
        // continue to write to a fifo buffer
        globalState.iobuff[globalState.buffend++] = inByte;
        inByte = 0;
        // check if the buffer is at capacity
        // (shouldn't ever happen under) normal circumstances
        if (globalState.buffend == 31)
        {
            // print buffer overflow error msg.
            fprintf(&mystdout, overflowMsg);
            // set index back to 0
            globalState.buffend = 0;
            // clear the buffer
            memset(globalState.iobuff, 0, 32 * sizeof(char));
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
