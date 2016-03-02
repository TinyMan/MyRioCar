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
}

void Capteur::initialiserUART(){

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
	}

int Capteur::trouverDistance()
{
	status = Uart_Open(&uart, BaudRate, DataBit,
							   Uart_StopBits1_0, Uart_ParityNone);
	if (status < VI_SUCCESS)
	{
		return status;
	}

	/*
	 * Writes data to a UART port.
	 */
	/*status = Uart_Write(&uart, &writeData, 1);
	if (status < VI_SUCCESS)
	{
		return status;
	}*/

	/*
	 * Reads data from a UART port.
	 */
	status = Uart_Read(&uart, &readData, 1);
	if (status < VI_SUCCESS)
	{
		return status;
	}

	//printf("The received data is %d \n", readData);

	status = Uart_Read(&uart, &readData, 1);
	if (status < VI_SUCCESS)
	{
		return status;
	}

	char c = (int) readData;
	distance[0] = c;

	//printf("The received data is %d \n", readData);

	status = Uart_Read(&uart, &readData, 1);
	if (status < VI_SUCCESS)
	{
		return status;
	}

	c = (int) readData;
	distance[1] = c;

	//printf("The received data is %d \n", readData);

	status = Uart_Read(&uart, &readData, 1);
	if (status < VI_SUCCESS)
	{
		return status;
	}

	c = (int) readData;
	distance[2] = c;

	//printf("The received data is %d \n", readData);

	//printf("LA VALEUR EST : ");
	int compteur;

	float d;

	/*for (compteur = 0 ; compteur < 3 ; compteur++)
	{
		printf("%c",distance[compteur]);

	}*/
	int i1 = distance[0] - '0';
	int i2 = distance[1] - '0';
	int i3 = distance[2] - '0';

	d = (i1*100+i2*10+i3)*2.54;
	//printf("Distance: %f \n", d);


	/*
	 * Clears UART receive buffer.
	 */
	status = Uart_Clear(&uart);
	if (status < VI_SUCCESS)
	{
		return status;
	}

	/*
	 * Closes the UART port.
	 */

	status = Uart_Close(&uart);
	if (status < VI_SUCCESS)
	{
		return status;
	}

	return d;
}
