#ifndef InfAacDecoder_h
#define InfAacDecoder_h

#include "InfDecoder.h"

#ifdef __cplusplus
extern "C" {
#endif

struct InfAacDecoder {
    void (**vtable)(void);
    int times;
};

void aac_ini(struct InfAacDecoder* thiz);
int aac_decode_frame(struct InfAacDecoder* thiz, int val);
int aac_get_times(struct InfAacDecoder* thiz);

extern void (*AacVtable[])();

#ifdef __cplusplus
}
#endif

#endif
