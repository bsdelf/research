#ifndef AacDecoder_h
#define AacDecoder_h

#include "Decoder.h"

#ifdef __cplusplus
extern "C" {
#endif

struct AacDecoder {
    const void* clazz;
    struct Decoder inf;
    int times;
};

extern const void* AacDecoder;

#ifdef __cplusplus
}
#endif

#endif
