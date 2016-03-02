/*
 * Batterie.h
 *
 *  Created on: 1 mars 2016
 *      Author: fllor_000
 */
#if !defined(LoopDuration)
#define LoopDuration    60  /* How long to output the signal, in seconds */
#endif
#include <stdio.h>
#include <time.h>
#include <AIO.h>
#include "MyRioHelper.h"


#ifndef BATTERIE_H_
#define BATTERIE_H_

class Batterie {
public:
	Batterie();
	virtual ~Batterie();
	void calculBatterie();
	int getBatterie();

private:
	int niveauBatterie;

	NiFpga_Status status;

    double ai_A0;
    double ai_A3;
    double ao_B0;

    MyRio_Aio A0;
    MyRio_Aio A3;
    MyRio_Aio B0;

    time_t currentTime;
    time_t finalTime;
};

#endif /* BATTERIE_H_ */
