// Author: Charles Lee - ccl002@ucsd.edu
// Provides a buffer service while alerting the client when pushed data is very different from items in the buffer.

#ifndef DIFF_BUFFER_H
#define DIFF_BUFFER_H

#include <CircularBuffer.h>

template<size_t size>
class DiffBuffer {
  public:
    DiffBuffer(double thresh) {
		this->thresh = thresh;
	}
	
	~DiffBuffer() {}
	
	bool push(int16_t item) {
		if (this->theBuffer.isFull()) {
			this->total -= this->theBuffer.first();
		}
		this->theBuffer.push(item);
		this->total += item;
		double diff = abs(item - (this->total / this->theBuffer.size()));
		if (diff > thresh) {
			return true;
		} else {
			return false;
		}
	}

	
  private:
	CircularBuffer<int16_t, size> theBuffer;
	int16_t total;
	double thresh;
};

#endif
