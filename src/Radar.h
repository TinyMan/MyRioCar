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

private:
	int angle, inc;
	float d;
	Capteur c;
	DirectionControl dc;
};



#endif /* RADAR_H_ */
