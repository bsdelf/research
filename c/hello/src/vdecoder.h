#ifndef VDECODER_H
#define VDECODER_H

#include <stdlib.h>
#include <stdio.h>

typedef void (*VirtualFunction)(void);

void pure_virtual_bad_call_hendler();

struct VTable {
    int d;
    int i;
    VirtualFunction fn;
};

struct VDecoder {
    int times;
    struct VTable* vtbl;
};

struct VDecoder* VDecoder_ctor(struct VDecoder* thiz);
void VDecoder_dtor(struct VDecoder* thiz);
int VDecoder_DecodeFrame(struct VDecoder* thiz, int val);

typedef int (*FnDecodeFrame)(void*, int);

#define VDecodeFrame(thiz, val) \
    ((FnDecodeFrame)thiz->vtbl[2].fn)(thiz, val)

#endif
