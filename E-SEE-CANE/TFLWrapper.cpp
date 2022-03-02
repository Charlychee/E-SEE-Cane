// Author: Charles Lee - ccl002@ucsd.edu

#include "TFLWrapper.h"

TFLWrapper::TFLWrapper(int16_t i2cAddr) {
	// Takes in the i2cAddr of the TF-Luna
	// Does NOT switch the I2C address, so make sure your TF-Luna
	// is on the given I2C address.
	this->i2cAddr = i2cAddr;
	this->theTFL = TFLI2C();
	this->dist = 0;
	this->flux = 0;
	this->temp = 0;
}

TFLWrapper::~TFLWrapper() {}

bool TFLWrapper::checkData() {
	// Asks the TFL for the data and updates this object's data fields (dist, flux, temp)
	// This function must be called before getting other data
	return theTFL.getData(this->dist, this->flux, this->temp, this->i2cAddr);
}

int16_t TFLWrapper::getDist() const {
	return this->dist;
}

int16_t TFLWrapper::getFlux() const {
	return this->flux;
}

int16_t TFLWrapper::getTemp() const {
	return this->temp;
}