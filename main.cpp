#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

ISR(USART_RX_vect){
  char inByte;

}

ISR(USART_TX_vect){

}

int main() {
  sei();                                              // set global interrupts
  while (true) {
    
  }
  return 1;
}
