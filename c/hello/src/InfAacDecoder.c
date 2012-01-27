#include "InfAacDecoder.h"

static struct InfTable InfTableForAac[] = {
    {
	(Vfn)aac_decode_frame
    },
    {
	(Vfn)aac_get_times
    }
};

void (*AacVtable[])() = {
    (Vfn)aac_decode_frame,
    (Vfn)aac_get_times
};

void aac_ini(struct InfAacDecoder* thiz) {
    //struct InfAacDecoder* thiz = MALLOC(struct InfAacDecoder);
    //thiz->itbl = InfTableForAac;
    thiz->vtable = AacVtable;
    thiz->times = 0;
}

int aac_decode_frame(struct InfAacDecoder* thiz, int val) {
    thiz->times++;
    return val+val;
}

int aac_get_times(struct InfAacDecoder* thiz) {
    return thiz->times;
}
