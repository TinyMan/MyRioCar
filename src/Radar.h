/*
 * Radar.h
 *
 *  Created on: 16 févr. 2016
 *      Author: fllor_000
 */

#include "Control.h"
#include "Capteur.h"


#ifndef RADAR_H_
#define RADAR_H_

class Radar{
public:
	Radar();
	virtual ~Radar();
	float utiliserRadar();
	void getTab(int *tab);

private:
	const int VALMIN = 15;
	const int VALMAX = 100;
	int angle, inc;
	float d;
	Capteur c;
	DirectionControl dc;
	int carte[90];
};



#endif /* RADAR_H_ */
