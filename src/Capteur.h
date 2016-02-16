/*
 * Capteur.h
 *
 *  Created on: 10 févr. 2016
 *      Author: fllor_000
 */

#ifndef CAPTEUR_H_
#define CAPTEUR_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "visa.h"
#include "UART.h"

#define BaudRate 9600
#define DataBit 8

class Capteur {
public:
	Capteur();
	virtual ~Capteur();
	int trouverDistance();
	void initialiserUART();


private:
	MyRio_Uart uart;
	uint8_t writeData;
	uint8_t readData;
	int32_t status;
	char distance[3];

};

#endif /* CAPTEUR_H_ */
