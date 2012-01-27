#ifndef Decoder_h
#define Decoder_h

#include "Object.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Decoder {
    int (*decode_frame)(void*, int);
    void* data;
};

int decode_frame(struct Decoder* self, int val);

#ifdef __cplusplus
}
#endif

#endif
