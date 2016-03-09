/*
 * Radar.cpp
 *
 *  Created on: 16 f�vr. 2016
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
#include <iostream>
using namespace std;


Radar::Radar() {
	// TODO Auto-generated constructor stub
	angle = -44;
	dc.setPwmUsed(MRio.Pwm.B1); dc.start();
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
		printf("angle: %d, Distance: %d\n", angle, d);
		/*if(angle == dc.MINANGLE || angle == dc.MAXANGLE){
			for(int i=dc.MINANGLE; i<=dc.MAXANGLE; i+=abs(inc)){
				printf("Val: %i: %i\n", i, carte[i]);
				//std::cout << "Val: " << i << ": " << carte[i];
			}
		}*/
		angle += inc;
		//usleep(70*1000);
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
