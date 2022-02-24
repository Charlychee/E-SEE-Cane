// Author: Charles Lee - ccl002@ucsd.edu

#ifndef TFLWrapper_H
#define TFLWrapper_H

#include "TFLI2C.h"

class TFLWrapper {
  public:
	TFLWrapper(int16_t  i2cAddr=TFL_DEF_ADR);
	~TFLWrapper();
	
	bool checkData(); // This function must run to update to the most recent data
	int16_t getDist() const;
	int16_t getFlux() const;
	int16_t getTemp() const;
	
  private:
	int16_t i2cAddr;
	TFLI2C theTFL;
	// device variables passed back by getData
	int16_t  dist;   // distance in centimeters
	int16_t  flux;   // signal quality in arbitrary units
	int16_t  temp;   // temperature in 0.01 degree Celsius
    
};

#endif