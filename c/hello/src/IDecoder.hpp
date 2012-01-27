#ifndef IDECODER_HPP
#define IDECODER_HPP
class IDecoder {
public:
    virtual int DecodeFrame(int val) = 0;
    virtual int GetTimes() = 0;
};
#endif
