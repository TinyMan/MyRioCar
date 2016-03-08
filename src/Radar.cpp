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
	stop();
	tid.join();
}


void Radar::utiliserRadar()
{
	int d;
	while(!_stop){
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

		carte[angle] = d;
		//printf("Distance: %f\n", d);
		if(angle == dc.MINANGLE || angle == dc.MAXANGLE){
			for(int i=1; i<=2*dc.MAXANGLE; i++){
				printf("Val: %i: %i\n", i, carte[i]);
				//std::cout << "Val: " << i << ": " << carte[i];
			}
		}
		angle = angle + inc;
	}

}

map<float,uint8_t>& Radar::getTab(){
	return carte;
}

void Radar::start() {
	_stop = false;
	tid = thread(&Radar::utiliserRadar, this);
}

void Radar::stop() {
	_stop=true;
}
