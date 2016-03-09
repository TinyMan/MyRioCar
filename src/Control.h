/*
 * Control.h
 *
 *  Created on: 9 févr. 2016
 *      Author: TinyMan
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "PWMHelper.h"

class SpeedControl{
private:
	//static constexpr float MINDUTYFORWARD = 0.068f;
	static constexpr float MAXDUTYFORWARD = 0.1005f;
	static constexpr float MINDUTYBACKWARD = 0.04324f;
	//static constexpr float MAXDUTYBACKWARD = 0.055f;
	static constexpr float NEUTRAL_DUTY = 0.07405f;
	Pwm& pwmUsed;

	float _speed = 0;
	bool _forward = true;
public:
	SpeedControl();

	/* set the speed and direction
	 * @param speed the speed in % (from 0.00 to 1.00)
	 * @param forward Optional set to false to go backward
	 */
	void setSpeed(float speed, bool forward = true);

	/* @return the direction; true = forward */
	bool getDirection() const { return _forward; }
	/* @return the current "target" speed (in %) */
	float getSpeed() const { return _speed; }
	Pwm& getPwmUsed()  { return pwmUsed;}
	void start() { pwmUsed.enable(); }
};
class DirectionControl {
private:
	Pwm pwmUsed;
	static constexpr float MINDUTY = 0.05f;
	static constexpr float MAXDUTY = 0.1f;

	float angle = 0;
public:
	DirectionControl();
	static constexpr float MAXANGLE = 45.0f; /* in degree */
	static constexpr float MINANGLE = -45.0f; /* in degree */
	/* set the angle from -45 to 45 degree */
	void setAngle(float angle);
	/* @return the angle in degree */
	float getAngle() const { return angle; }
	/* set the pwm used (by ref)
	 * ex: control.setPwmUsed(MRio.Pwm.A0)
	 */
	void setPwmUsed(const Pwm& pwm) { pwmUsed = pwm; pwmUsed.setFrequency(FREQUENCY_50HZ);}
	Pwm getPwmUsed() const { return pwmUsed;}
	void start() { pwmUsed.enable(); }
	void stop() { pwmUsed.disable();}
};
class Control {
public:
	Control();
	virtual ~Control();

	SpeedControl Speed;
	DirectionControl Direction;
};

#endif /* CONTROL_H_ */
