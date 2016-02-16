#include <iostream>
#include "MyRioHelper.h"
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include "Capteur.h"
#include <unistd.h>
#include <cstdio>
#include "MyRioCar.h"
#include "Radar.h"

using namespace std;

int main() {

	/*float d;
	Capteur cap;
	//DirectionControl dc;
	//dc.setPwmUsed(MRio.Pwm.A0);
	int angle = -45;
	while(1){
		d = cap.trouverDistance();
		if (angle < 45){
			angle++;
		}
		else{
			angle --;
		}
		dc.setAngle(angle);
		printf("Distance: %f\n", d);
		sleep(1);
	}*/

	printf("Testing control\n");

		//MyRioCar Car;

		 /* Normally, the main function runs a long running or infinite loop.
		 * Keep the program running for 60 seconds so that the PWM output can be
		 * observed using an external instrument.
		 */

		/*float a = 45;
		//Car.start();
		//Car.Control.Speed.setSpeed(0.1);
		//Car.Control.Speed.getPwmUsed().setDuty(0.069);
		time_t currentTime;
		time_t finalTime;
		time_t startTime;
		time(&startTime);
		time(&currentTime);
		finalTime = currentTime + 10;
		time_t nextInvert = currentTime;
		using namespace std;
		DirectionControl dc; dc.setPwmUsed(MRio.Pwm.A2); dc.start();
		while (currentTime < finalTime) {
			if (currentTime >= nextInvert) {
				std::cout << "currnet time: " << currentTime - startTime << "\n";
				//Car.Control.Speed.setSpeed(a = 1-a);
				//Car.Control.Direction.setAngle(a = -a);
				dc.setAngle(a=-a);
				nextInvert = currentTime + 1;
			}
			time(&currentTime);
		}*/
	Radar r;
	r.utiliserRadar();

	return 0;
}

