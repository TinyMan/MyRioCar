/*
 * Capteur.cpp
 *
 *  Created on: 10 févr. 2016
 *      Author: fllor_000
 */

#include "Capteur.h"
#include "UART.h"
Capteur::Capteur() {
	// TODO Auto-generated constructor stub

	initialiserUART();
}

Capteur::~Capteur() {
	// TODO Auto-generated destructor stub
	/*
	 * Closes the UART port.
	 */

	status = Uart_Close(&uart);

}

void Capteur::initialiserUART() {

	writeData = 'H';
	uint8_t readData = 0;
	int32_t status = 0;
	char distance[3];

	/*
	 * Initialize the UART port structure.
	 */
	uart.name = "ASRL1::INSTR";
	uart.defaultRM = 0;
	uart.session = 0;

	status = Uart_Open(&uart, BaudRate, DataBit, Uart_StopBits1_0,
			Uart_ParityNone);
	if (status < VI_SUCCESS) {
		throw status;
	}
}

int Capteur::trouverDistance() {


	unsigned char distance[4];
	Uart_Read(&uart, distance, 4);



	float d;

	int i1 = distance[1] - '0';
	int i2 = distance[2] - '0';
	int i3 = distance[3] - '0';

	d = (i1 * 100 + i2 * 10 + i3) * 2.54;
	//printf("Distance: %f \n", d);

	/*
	 * Clears UART receive buffer.
	 */
	status = Uart_Clear(&uart);
	if (status < VI_SUCCESS) {
		return status;
	}

	return d;
}
