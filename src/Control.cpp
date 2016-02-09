/*
 * Control.cpp
 *
 *  Created on: 9 févr. 2016
 *      Author: TinyMan
 */

#include "Control.h"
#include "MyRioHelper.h"
#include <string>

Control::Control() {
	// TODO Auto-generated constructor stub

}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

SpeedControl::SpeedControl() : pwmUsed(MRio.Pwm.A0)
{
	pwmUsed.setFrequency(FREQUENCY_50HZ);
}

void SpeedControl::setSpeed(float speed, bool forward) {
	if(speed < 0 || speed > 1)  throw "Speed should be between 0 and 1";

	float duty = 0;
	if(forward){
		duty = MINDUTYFORWARD + (MAXDUTYFORWARD - MINDUTYFORWARD) * speed;
	} else {
		duty = MAXDUTYBACKWARD - (MAXDUTYBACKWARD - MINDUTYBACKWARD) * speed;
	}
	pwmUsed.setDuty(duty);
}

DirectionControl::DirectionControl() : pwmUsed(MRio.Pwm.A1)
{
	pwmUsed.setFrequency(FREQUENCY_50HZ);
}

void DirectionControl::setAngle(float angle) {
	if(angle < MINANGLE || angle > MAXANGLE) {
		throw "Angle should be between -45 and 45";
	}
	this->angle = angle;
	float duty = MINDUTY + (MAXDUTY - MINDUTY) * ((angle - MINANGLE) / (MAXANGLE - MINANGLE));
	pwmUsed.setDuty(duty);
}
