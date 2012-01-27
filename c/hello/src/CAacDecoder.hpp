#ifndef CAACDECODER_HPP
#define CAACDECODER_HPP
#include "IDecoder.hpp"

class CAacDecoder: public IDecoder {
public:
    CAacDecoder():
	mTimes(0) { }

public:
    virtual int DecodeFrame(int val) {
	mTimes++;
	return val+val;
    }

    virtual int GetTimes() {
	return mTimes;
    }

private:
    int mTimes;
};


#endif
