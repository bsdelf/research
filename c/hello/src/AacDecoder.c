#include "Object.h"
#include "AacDecoder.h"
#include "stdio.h"

static inline int o_aac_decode_frame(void* _self, int val); 

static void* AacDecoder_ctor(void* _self, va_list* args)
{
    struct AacDecoder* self = _self;
    self->inf.decode_frame = &o_aac_decode_frame;
    self->inf.data = _self;
    return self;
}

static void* AacDecoder_dtor(void* _self)
{
    struct AacDecoder* self = _self;
    return self;
}

static void* AacDecoder_clone(const void* _self)
{
    return create(AacDecoder);
}

static int AacDecoder_differ(const void* _self, const void* _b)
{
    const struct AacDecoder* self = _self;
    const struct AacDecoder* b = _b;
    
    if (self == b)
	return 0;
    if (!b || b->clazz != AacDecoder)
	return 1;
    else
	return -1;
}

static inline int o_aac_decode_frame(void* _data, int val) {
    struct AacDecoder* data = _data;
    data->times++;
    return val+val;
}

static const struct Meta _AacDecoder = {
    sizeof(struct AacDecoder),
    AacDecoder_ctor,
    AacDecoder_dtor,
    AacDecoder_clone,
    AacDecoder_differ,
};

const void* AacDecoder = &_AacDecoder;
