// Author: Charles Lee - ccl002@ucsd.edu

#include "Timer.h"
#include "Arduino.h"

Timer::Timer(int interval, void (*function)()) {
	this->previous = millis();
	this->theInterval = interval;
	this->theFunction = function;
}

Timer::~Timer() {}

void Timer::run() {
	if (millis() - this->previous > this->theInterval) {
		this->theFunction();
		this->previous = millis();
	}
}
