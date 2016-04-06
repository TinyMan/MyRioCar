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

int main(int argc, char* argv[]) {
	try {
		printf("Testing control\n");

		MyRioCar Car;

		/* Normally, the main function runs a long running or infinite loop.
		 * Keep the program running for 60 seconds so that the PWM output can be
		 * observed using an external instrument.
		 */

		bool quit = false;
		const uint8_t MINDISTANCE = 50; // cm
		const uint8_t STOP = 20;

		Radar r;
		r.start();

		r.setPrecision(10);
		RemoteControl rc(Car, r);
		rc.startServer(1337);
		Car.start();


		time_t currentTime;
		time_t finalTime;
		time_t startTime;
		time(&startTime);
		time(&currentTime);

		finalTime = currentTime + 150;


		map <float, uint8_t>& arr = r.getTab();
		auto it = arr.begin();

		bool flag =  false;
		bool stop = false;
		int c = 0;
		const int nbValMin = 1; // nombre de valeur pour qu'on considere qu'il y a vraiment un obstacle

		float angle = 0;
		float speed = 0.0;
		if(argc > 1)
			speed = atof(argv[1]);
		//sleep(1);
		//Car.Control.Direction.setAngle(angle);
		//Car.Control.Speed.setSpeed(speed);
		while (currentTime < finalTime && !stop) {

			it = arr.begin();
			flag = false;
			c = 0;


			// check if there is an obstacle in front of the car
			/*while (c <= nbValMin && it != arr.end()){
				flag = it->second < MINDISTANCE;
				stop = it->second < STOP;
				if(flag)c++;
				++it;
			}*/
			uint8_t distance = r.getLastPoint().distance;
			stop = distance < STOP;

			//printf( "distance : %d \n" ,  distance );

			speed = distance / 10000.;
			speed = speed >= 0.01 ? speed : 0;

			//cout << c << " ";
			if(distance < MINDISTANCE){ // there is an obstacle
				angle = -45;
				//cout << "TURNING" << endl;
			} else {
				angle = 0;
				//cout << "FORWARD" << endl;
			}



			//Car.Control.Direction.setAngle(angle);
			//cout << "Speed " << speed << endl;
			//Car.Control.Speed.setSpeed(speed);

			time(&currentTime);
			usleep(1000 * 100*10); // 10MS
		}

		Car.Control.Direction.setAngle(0);
		Car.Control.Speed.setSpeed(0);
		rc.stop();
		r.stop();

		cout << "end " << endl;
	} catch (const char* e) {
		cout << e << endl;
	}
	return 0;
}

