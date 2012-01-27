#include "vaacdecoder.h"

struct VTable VTableArrayForAacDecoder[] = {
    {
	0, 0, (VirtualFunction)VAacDecoder_ctor
    },
    {
	0, 0, (VirtualFunction)VAacDecoder_dtor
    },
    {
	0, 0, (VirtualFunction)VAacDecoder_DecodeFrame
    }
};

struct VAacDecoder* VAacDecoder_ctor(struct VAacDecoder* thiz) {
    if (thiz == NULL) {
	thiz = (struct VAacDecoder*) malloc(sizeof(struct VAacDecoder));
    }

    if (thiz) {
	VDecoder_ctor((struct VDecoder*)thiz);
	thiz->vtbl = VTableArrayForAacDecoder;

	thiz->test = 1987;
    }

    return thiz;
}

void VAacDecoder_dtor(struct VAacDecoder* thiz) {
    thiz->vtbl = VTableArrayForAacDecoder;
    VDecoder_dtor((struct VDecoder*) thiz);
    free(thiz);
}

int VAacDecoder_DecodeFrame(struct VAacDecoder* thiz, int val) {
    thiz->times++;
    return val+val;
}
