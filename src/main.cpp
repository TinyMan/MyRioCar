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

		bool quit = false;
		const uint8_t MINDISTANCE = 50; // cm

		Radar r;
		r.start();
		r.setPrecision(1);
		RemoteControl rc(Car, r);
		rc.startServer(1337);
		Car.start();

		time_t currentTime;
		time_t finalTime;
		time_t startTime;
		time(&startTime);
		time(&currentTime);

		finalTime = currentTime + 20;


		map <float, uint8_t>& arr = r.getTab();
		auto it = arr.begin();

		bool flag =  false;
		int c = 0;
		const int nbValMin = 3; // nombre de valeur pour qu'on considere qu'il y a vraiment un obstacle

		float angle = 0;
		float speed = 0.16;
		//Car.Control.Direction.setAngle(a);
		//Car.Control.Speed.setSpeed(speed);
		while (currentTime < finalTime) {

			it = arr.begin();
			flag = false;
			c = 0;


			// check if there is an obstacle in front of the car
			while (c <= nbValMin && it != arr.end()){
				flag = it->second < MINDISTANCE;
				if(flag)c++;
				++it;
			}

			cout << c << " ";
			if(c >= nbValMin){ // there is an obstacle
				angle = -45;
				cout << "TURNING" << endl;
			} else {
				angle = 0;
				cout << "FORWARD" << endl;
			}



			Car.Control.Direction.setAngle(angle);
			//Car.Control.Speed.setSpeed(speed);

			time(&currentTime);
			usleep(1000 * 1000);
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

