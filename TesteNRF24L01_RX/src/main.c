/*
 * main.c
 *
 *  Created on: 19/04/2016
 *      Author: patrizio
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include <rs485.h>
#include <nrf24l01.h>

int main(void) {
	uint8_t i = 0;
	uint8_t bufferin[NRF24L01_PAYLOAD];

	initRS485();
	_delay_ms(100);
	rs485SetWrite();
	_delay_ms(10);

	nrf24l01_init();

	sei();

	uint8_t pipe = 1;
	uint8_t addrrx1[NRF24L01_ADDRSIZE] = NRF24L01_ADDRP1;
	nrf24l01_setrxaddr(pipe, addrrx1);

	for (i = 0; i < sizeof(bufferin); i++)
		bufferin[i] = 0;

	for (;;) {
		// if data is ready
		if (nrf24l01_readready(&pipe)) {
			nrf24l01_read(bufferin);

			writeRS485(bufferin);
			while (!rs485TransmitComplete()) {
				_delay_ms(10);
			}
		}

		_delay_ms(10);
	}

	return 0;
}
