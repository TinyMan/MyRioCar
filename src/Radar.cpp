/*
 * Radar.cpp
 *
 *  Created on: 16 févr. 2016
 *      Author: fllor_000
 */

#include "Radar.h"
#include "MyRioCar.h"
#include "MyRioHelper.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>


Radar::Radar() {
	// TODO Auto-generated constructor stub
	angle = -44;
	dc.setPwmUsed(MRio.Pwm.A2); dc.start();
	inc = 1;
}

Radar::~Radar() {
	// TODO Auto-generated destructor stub
}


float Radar::utiliserRadar()
{
	while(1){
		d = c.trouverDistance();
		dc.setAngle(angle);
		if (angle <= dc.MINANGLE || angle >= dc.MAXANGLE){
			inc = inc * -1;
		}
		printf("Distance: %f\n", d);
		angle = angle + inc;
		//sleep(1/90);
	}
	return 0;
}
