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
	carte[0] = 0;
}

Radar::~Radar() {
	// TODO Auto-generated destructor stub
}


float Radar::utiliserRadar()
{
	while(1){
		d = c.trouverDistance();
		dc.setAngle(angle);

		if (d<VALMIN){
			if(inc>0) d = carte[int(dc.MAXANGLE+angle)-1];
			else d = carte[int(dc.MAXANGLE+angle)+1];
		}

		else if(d>VALMAX){
			d = 0;
		}

		if (angle <= dc.MINANGLE || angle >= dc.MAXANGLE){
			inc = inc * -1;
		}

		carte[int(dc.MAXANGLE+angle)] = d;
		//printf("Distance: %f\n", d);
		if(angle == dc.MINANGLE || angle == dc.MAXANGLE){
			for(int i=1; i<=2*dc.MAXANGLE; i++){
				printf("Val: %i: %i\n", i, carte[i]);
				//std::cout << "Val: " << i << ": " << carte[i];
			}
		}
		angle = angle + inc;
		sleep(1/90);
	}
	return 0;
}

void Radar::getTab(int *tab){
	tab=carte;
}
