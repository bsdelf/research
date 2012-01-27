#ifndef InfMp3Decoder_h
#define InfMp3Decoder_h

#include "InfDecoder.h"

#ifdef __cplusplus
extern "C" {
#endif

struct InfMp3Decoder {
    void (**vtable)(void);
    int times;
};

void mp3_ini(struct InfMp3Decoder* thiz);
int mp3_decode_frame(struct InfMp3Decoder* thiz, int val);
int mp3_get_times(struct InfMp3Decoder* thiz);

extern void (*Mp3Vtable[])();

#ifdef __cplusplus
}
#endif

#endif
