#include "car.h"

Car::Car(Adafruit_DotStar* strip) {
	this->strip = strip;

	this->create();
}

bool Car::create() {
	randomSeed(analogRead(0));

	this->startLed = random(0, 60);
	this->endLed = random(0, 60);
	this->head = this->startLed;

	if (this->startLed < this->endLed) {
		this->directionDifference = 1;
		this->tail = this->head - 2;
	} else {
		this->directionDifference = -1;
		this->tail = this->head + 2;
	}

	this->active = false;

	return true;
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
