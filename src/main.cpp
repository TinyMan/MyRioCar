#include <iostream>
#include "MyRioHelper.h"
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include "Capteur.h"
#include <unistd.h>

using namespace std;

int main() {

	float d;
	Capteur cap;
	DirectionControl dc;
	dc.setPwmUsed(MRio.Pwm.A0);
	int angle = -45;
	while(1){
		//d = cap.trouverDistance();
		if (angle < 45){
			angle++;
		}
		else{
			angle --;
		}
		dc.setAngle(angle);
		//printf("Distance: %f\n", d);
		sleep(1);
	}


	return 0;
}

