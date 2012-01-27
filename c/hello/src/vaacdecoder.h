#ifndef VAACDECODER_H
#define VAACDECODER_H 

#include "vdecoder.h"

#ifdef __cplusplus
extern "C" {
#endif

struct VAacDecoder {
    int times;
    struct VTable* vtbl;

    int test;
};

struct VAacDecoder* VAacDecoder_ctor(struct VAacDecoder* thiz);
void VAacDecoder_dtor(struct VAacDecoder* thiz);
int VAacDecoder_DecodeFrame(struct VAacDecoder* thiz, int val);

#ifdef __cplusplus
}
#endif

#endif
