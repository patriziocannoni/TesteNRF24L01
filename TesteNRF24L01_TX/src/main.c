/*
 * main.c
 *
 *  Created on: 19/04/2016
 *      Author: patrizio
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include <nrf24l01.h>

int main(void) {
	uint8_t bufferout[NRF24L01_PAYLOAD] = "HELLO WORLD !!!\n";

	nrf24l01_init();

	sei();

	uint8_t addrtx1[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP1;

	//set tx address for pipe 1
	nrf24l01_settxaddr(addrtx1);

	for (;;) {
		nrf24l01_write(bufferout);
		_delay_ms(1000);
	}

	return 0;
}
