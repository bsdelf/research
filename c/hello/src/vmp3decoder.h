#ifndef VMP3DECODER_H
#define VMP3DECODER_H

#include "vdecoder.h"

#ifdef __cplusplus
extern "C" {
#endif

struct VMp3Decoder {
    int times;
    struct VTable* vtbl;

    const char* desc;
};

struct VMp3Decoder* VMp3Decoder_ctor(struct VMp3Decoder* thiz);
void VMp3Decoder_dtor(struct VMp3Decoder* thiz);
int VMp3Decoder_DecodeFrame(struct VMp3Decoder* thiz, int val);

#ifdef __cplusplus
}
#endif

#endif
