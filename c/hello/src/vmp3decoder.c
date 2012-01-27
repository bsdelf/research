#include "vmp3decoder.h"

struct VTable VTableArrayForMp3Decoder[] = {
    {
	0, 0, (VirtualFunction)VMp3Decoder_ctor
    },
    {
	0, 0, (VirtualFunction)VMp3Decoder_dtor
    },
    {
	0, 0, (VirtualFunction)VMp3Decoder_DecodeFrame
    }
};

struct VMp3Decoder* VMp3Decoder_ctor(struct VMp3Decoder* thiz) {
    if (thiz == NULL) {
	thiz = (struct VMp3Decoder*) malloc(sizeof(struct VMp3Decoder));
    }

    if (thiz) {
	VDecoder_ctor((struct VDecoder*)thiz);
	thiz->vtbl = VTableArrayForMp3Decoder;

	thiz->desc = "im mp3 decoder";
    }

    return thiz;
}

void VMp3Decoder_dtor(struct VMp3Decoder* thiz) {
    thiz->vtbl = VTableArrayForMp3Decoder;
    VDecoder_dtor((struct VDecoder*) thiz);
    free(thiz);
}

int VMp3Decoder_DecodeFrame(struct VMp3Decoder* thiz, int val) {
    thiz->times++;
    return val*val;
}
