#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "strings.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

char message[32];
int i = 0;

ISR(USART_RX_vect){
  char inByte = UDR0;
  // processing goes here
  if (inByte=='\n') {
    i = 0;
    // process string here
    
    // clear message buffer when done
    memset(message, 0, sizeof message);
  } else {
    // continue to write to a fifo buffer
    message[i++] = inByte;
    inByte = 0;
  }
}

ISR(USART_TX_vect){

}

int main() {
  // UART init code
  UBRR0H = (BAUD_PRESCALE>>8);
  UBRR0L = BAUD_PRESCALE;
  UCSR0B = (1<<RXEN0) | (1<<RXCIE0);
  UCSR0C |= (1<<UCSZ00 | (1 << UCSZ01));
  // set global interrupts
  sei();
  while (true) {
    
  }
  return 1;
}
