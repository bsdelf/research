#ifndef Mp3Decoder_h
#define Mp3Decoder_h

#include "Decoder.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Mp3Decoder {
    const void* meta;
    struct Decoder inf;
    int times;
};

extern const void* Mp3Decoder;

#ifdef __cplusplus
}
#endif

#endif
