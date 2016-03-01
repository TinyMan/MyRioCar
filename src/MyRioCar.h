/*
 * MyRioCar.h
 *
 *  Created on: 10 févr. 2016
 *      Author: TinyMan
 */

#ifndef MYRIOCAR_H_
#define MYRIOCAR_H_

#include "Control.h"
#include "DioHelper.h"

class MyRioCar {
private:
	Dio carSwitch;

public:
	class Control Control;

	MyRioCar();
	void start();
	void stop();

	virtual ~MyRioCar();
};

#endif /* MYRIOCAR_H_ */

