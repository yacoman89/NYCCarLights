#include "car.h"

Car::Car(uint32_t* leds, int ledCount, int number) {
	this->leds = leds;
	this->number = number;

	this->ledLength = ledCount;
	Serial.println(this->ledLength);

	this->create();
}

bool Car::create() {
	randomSeed(analogRead(0));

	this->startLed = random(0, 60);
	this->endLed = random(0, 60);
	this->head = this->startLed;

	if (this->startLed < this->endLed) {
		this->directionDifference = 1;
		this->tail = this->head - 1;
	} else {
		this->directionDifference = -1;
		this->tail = this->head + 1;
	}

	this->active = false;

	return this->number;
}

bool Car::isActive() {
	return this->active;
}

bool Car::setActive(bool active) {
	this->active = active;

	return active;
}

int Car::getStart() {
	return this->startLed;
}

int Car::getEnd() {
	return this->endLed;
}

int Car::getHead() {
	return this->head;
}

int Car::getTail() {
	return this->tail;
}

int Car::getPathLength() {
	if (this->directionDifference == 1)
		return this->endLed - this->startLed;
	else
		return this->startLed - this->endLed;
}

bool Car::nextStep() {

	if (this->active) {

		if (this->directionDifference > 0) {
			this->head++;
			this->tail++;
		} else {
			this->head--;
			this->tail--;
		}

		int headTemp, tailTemp;

		if (head < 0)
			headTemp = 0;
		else if (head > this->ledLength - 1)
			headTemp = this->ledLength - 1;
		else
			headTemp = head;

		if (tail < 0)
			tailTemp = 0;
		else if (tail > this->ledLength - 1)
			tailTemp = this->ledLength - 1;
		else
			tailTemp = tail;

		leds[headTemp] = 0x050505;
		leds[tailTemp] = 0x050505;

		if (tailTemp == this->endLed || headTemp == this->endLed)
			this->active = false;	
	}

	return this->active;
}
