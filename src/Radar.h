/*
 * Radar.h
 *
 *  Created on: 16 févr. 2016
 *      Author: fllor_000
 */
#ifndef RADAR_H_
#define RADAR_H_

#include "Control.h"
#include "Capteur.h"
#include "RemoteControl/protocol.h"
#include <thread>
#include <map>
using namespace std;

class Radar {
public:
	Radar();
	virtual ~Radar();
	void utiliserRadar();
	map<float, uint8_t>& getTab();

	void start();
	void stop();

	us_point getLastPoint() {
		return {
			float(angle),
			d
		};
	}

	/* set the precision (degree inc) */
	void setPrecision(int precision = 1) {
		inc = precision;
		carte.clear();
	}
private:
	const int VALMIN = 15;
	const int VALMAX = 500;
	int angle, inc;
	Capteur c;
	DirectionControl dc;
	map<float, uint8_t> carte;

	thread* tid = nullptr;
	bool _stop = false;
	uint8_t d;
};

#endif /* RADAR_H_ */
