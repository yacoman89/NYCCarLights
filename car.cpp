#include "car.h"

Car::Car(Adafruit_DotStar* strip) {
	this->strip = strip;

	// hex   Green Red   Blue
	// 0x    00    00    00
	uint32_t colorList[] = { 0x000000
		                   , 0x010101
		                   , 0x020202
		                   , 0x030303
		                   , 0x040404
		                   , 0x050505
		                   };
    this->colorLength = sizeof(colorList)/sizeof(uint32_t);
    this->colors = new uint32_t[this->colorLength];
    this->colors = colorList;

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

	this->lightStep = 0;
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

bool Car::nextStep() {
	Serial.println((int)this->strip);
	this->strip->setPixelColor(25, 0x101010);

	// if (this->active) {
	// 	if ((this->directionDifference > 0) && (this->lightStep == this->colorLength)) {
	// 		this->lightStep = 0;
	// 		this->head++;
	// 		this->tail++;
	// 	} else {
	// 		this->lightStep++;
	// 		this->strip->setPixelColor(head, this->colors[this->lightStep]);
	// 		this->strip->setPixelColor(tail, this->colors[this->colorLength - this->lightStep - 1]);
	// 	}

	// 	if ((this->tail == this->endLed) && (this->lightStep == this->colorLength))
	// 		this->active = false;
	// }

	return this->active;
}
