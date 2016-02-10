/*
 * MyRioCar.cpp
 *
 *  Created on: 10 févr. 2016
 *      Author: TinyMan
 */

#include "MyRioCar.h"

MyRioCar::MyRioCar() {
	// TODO Auto-generated constructor stub

}

MyRioCar::~MyRioCar() {
	// TODO Auto-generated destructor stub
}

void MyRioCar::start() {
	Control.Direction.start();
	Control.Speed.start();
}

void MyRioCar::stop() {
}
