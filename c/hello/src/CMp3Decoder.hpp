#ifndef CMP3DECODER_HPP
#define CMP3DECODER_HPP

#include "IDecoder.hpp"

class CMp3Decoder: public IDecoder {
public:
    CMp3Decoder():
	mTimes(0) { }

    virtual int DecodeFrame(int val) {
	mTimes++;
	return val*val;
    }

    virtual int GetTimes() {
	return mTimes;
    }

private:
    int mTimes;
};


#endif
