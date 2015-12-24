#ifndef CAR_H
#define CAR_H

#include "Arduino.h"

class Car {
	private:
		uint32_t* leds;
		int ledLength;

		int startLed;
		int endLed;
		int directionDifference;
		int head;
		int tail;
		bool active;
		int number;

		uint32_t on;

	public:
		Car(uint32_t* leds, int ledCount, int number);
		bool create();
		bool isActive();
		bool setActive(bool active);
		int getStart();
		int getEnd();
		int getHead();
		int getTail();
		int getPathLength();
		bool nextStep();
};

#endif
