#include "InfMp3Decoder.h"

static struct InfTable InfTableForMp3[] = {
    {
	(Vfn)mp3_decode_frame
    },
    {
	(Vfn)mp3_get_times
    }
};

void (*Mp3Vtable[])() = {
    (Vfn)mp3_decode_frame,
    (Vfn)mp3_get_times
};

void mp3_ini(struct InfMp3Decoder* thiz) {
    //struct InfMp3Decoder* thiz = MALLOC(struct InfMp3Decoder);
    //thiz->itbl = InfTableForMp3;
    thiz->vtable = Mp3Vtable;
    thiz->times = 0;
}

int mp3_decode_frame(struct InfMp3Decoder* thiz, int val) {
    thiz->times++;
    return val*val;
}

int mp3_get_times(struct InfMp3Decoder* thiz) {
    return thiz->times;
}
