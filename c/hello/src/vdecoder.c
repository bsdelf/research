#include "vdecoder.h"

void pure_virtual_bad_call_hendler() {
    printf("bad call!\n");
}

struct VTable VTableArrayForDecoder[] = {
    {
	0, 0, (VirtualFunction)pure_virtual_bad_call_hendler
    },
    {
	0, 0, (VirtualFunction)VDecoder_dtor
    },
    {
	0, 0, (VirtualFunction)pure_virtual_bad_call_hendler
    }
};

struct VDecoder* VDecoder_ctor(struct VDecoder* thiz) {
    if (thiz == NULL) {
	thiz = (struct VDecoder*) malloc(sizeof(struct VDecoder));
    }
    return thiz;
}

void VDecoder_dtor(struct VDecoder* thiz) {
}
