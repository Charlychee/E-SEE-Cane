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
  // Check if enough time as passed before running the function (Synchronous)
	if (millis() - this->previous > this->theInterval) {
		this->runNow();
	}
}

void Timer::runNow() {
  // Run the function right now (Asynchronous)
  this->theFunction();
  this->previous = millis();
}
