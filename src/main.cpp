#include <iostream>
#include "MyRioHelper.h"
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include "Capteur.h"
#include <unistd.h>
#include <cstdio>
#include "MyRioCar.h"
#include "MyRioHelper.h"
#include "AccelerometerHelper.h"
#include "RemoteControl/RemoteControl.h"
#include "Radar.h"

using namespace std;

int main() {
	try {
		printf("Testing control\n");

		MyRioCar Car;

		/* Normally, the main function runs a long running or infinite loop.
		 * Keep the program running for 60 seconds so that the PWM output can be
		 * observed using an external instrument.
		 */


		Radar r;
		r.start();
		r.setPrecision(5);
		RemoteControl rc(Car, r);
		rc.startServer(1337);
		Car.start();

		time_t currentTime;
		time_t finalTime;
		time_t startTime;
		time(&startTime);
		time(&currentTime);

		finalTime = currentTime + 15;
		time_t nextInvert = currentTime + 1;

		float a = -45;
		float b = 0.1;
		//Car.Control.Direction.setAngle(a);
		//Car.Control.Speed.setSpeed(b);
		while (currentTime < finalTime) {
			if (currentTime >= nextInvert) {
				//cout << "Main loop running" << endl;
				nextInvert = currentTime + 1;
				//Car.Control.Direction.setAngle(a=-a);
				//Car.Control.Speed.setSpeed(b+=0.002);
			}
			time(&currentTime);
			sleep(1);
		}

		Car.Control.Speed.setSpeed(0);
		rc.stop();
		r.stop();

		cout << "end " << endl;
	} catch (const char* e) {
		cout << e << endl;
	}
	return 0;
}

