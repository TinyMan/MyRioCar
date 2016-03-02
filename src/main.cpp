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

using namespace std;

int main() {
	try {
		printf("Testing control\n");

		MyRioCar Car;

		/* Normally, the main function runs a long running or infinite loop.
		 * Keep the program running for 60 seconds so that the PWM output can be
		 * observed using an external instrument.
		 */
		Car.start();

		RemoteControl rc(Car);
		rc.startServer(1337);

		time_t currentTime;
		time_t finalTime;
		time_t startTime;
		time(&startTime);
		time(&currentTime);

		finalTime = currentTime + 60;
		time_t nextInvert = currentTime + 1;

		while (currentTime < finalTime) {
			if (currentTime >= nextInvert) {
				//cout << "Main loop running" << endl;
				nextInvert = currentTime + 10;
			}
			time(&currentTime);
			sleep(1);
		}

		rc.stop();

		cout << "end " << endl;
	} catch (const char* e) {
		cout << e << endl;
	}
	return 0;
}

