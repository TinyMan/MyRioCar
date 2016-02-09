#include <iostream>
#include "MyRioHelper.h"

using namespace std;

int main() {
	printf("PWM\n");

	Pwm& pwm = MRio.Pwm.A0;
	//pwm.setFrequency(FREQUENCY_50HZ);
	/* should be equivalent to:
	 */pwm.clockSelect(Pwm_32x);
	pwm.counterMax(25000);
	//pwm.counterMax(1000);
	//pwm.counterCompare(20000);
	/**/

	pwm.enable();

	float dutyCycle = 0.035;
	float i = 0.001;
	pwm.setDuty(dutyCycle);
	/*
	 * Normally, the main function runs a long running or infinite loop.
	 * Keep the program running for 60 seconds so that the PWM output can be
	 * observed using an external instrument.
	 */

	time_t currentTime;
	time_t finalTime;
	time(&currentTime);
	finalTime = currentTime + 60;
	time_t nextInvert = currentTime;
	using namespace std;
	while (currentTime < finalTime) {
		//std::cout << "inner loop\n";
		if (currentTime >= nextInvert) {
			if (dutyCycle <= 0.00 || dutyCycle >= 0.15)
				i = -i;
			dutyCycle = dutyCycle + i;
			pwm.setDuty(dutyCycle);
			cout << dutyCycle << endl;
			nextInvert = currentTime + 1;
		}
		time(&currentTime);
	}

	return 0;
}

