#ifndef CAR_H
#define CAR_H

#include "Arduino.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

class Car {
	private:
		Adafruit_DotStar* strip;
		int startLed;
		int endLed;
		int directionDifference;
		int head;
		int tail;
		bool active;

	public:
		Car(Adafruit_DotStar* strip);
		bool create();
		bool isActive();
		bool setActive(bool active);
		int getStart();
		int getEnd();
		int getHead();
		int getTail();
		int getPathLength();
};

#endif
