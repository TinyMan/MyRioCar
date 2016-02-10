#include <iostream>
#include <cstdio>
#include "MyRioCar.h"

using namespace std;

int main() {
	printf("Testing control\n");

	MyRioCar Car;

	 /* Normally, the main function runs a long running or infinite loop.
	 * Keep the program running for 60 seconds so that the PWM output can be
	 * observed using an external instrument.
	 */

	float a = 45;
	Car.start();
	Car.Control.Speed.setSpeed(0.1);
	//Car.Control.Speed.getPwmUsed().setDuty(0.069);
	time_t currentTime;
	time_t finalTime;
	time_t startTime;
	time(&startTime);
	time(&currentTime);
	finalTime = currentTime + 10;
	time_t nextInvert = currentTime;
	using namespace std;
	while (currentTime < finalTime) {
		if (currentTime >= nextInvert) {
			std::cout << "currnet time: " << currentTime - startTime << "\n";
			//Car.Control.Speed.setSpeed(a = 1-a);
			Car.Control.Direction.setAngle(a = -a);
			nextInvert = currentTime + 1;
		}
		time(&currentTime);
	}


	return 0;
}

