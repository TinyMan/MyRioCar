/*
 * MyRioCar.cpp
 *
 *  Created on: 10 févr. 2016
 *      Author: TinyMan
 */

#include "MyRioCar.h"

MyRioCar::MyRioCar() : carSwitch(Dio::A70, 0) {
	// TODO Auto-generated constructor stub

}

MyRioCar::~MyRioCar() {
	// TODO Auto-generated destructor stub
}

void MyRioCar::start() {
	carSwitch.write(true); // switch the car on (we have 3 sec to send neutral pwm to the speed regulator)
	Control.Direction.start();
	Control.Speed.start();
}

void MyRioCar::stop() {
	carSwitch.write(false);
}
