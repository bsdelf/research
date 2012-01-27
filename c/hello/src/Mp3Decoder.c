#include "Object.h"
#include "Mp3Decoder.h"
#include "stdio.h"

static int o_mp3_decode_frame(void* _meta, int val); 

static void* Mp3Decoder_ctor(void* _data, va_list* args) {
    struct Mp3Decoder* data = _data;
    data->inf.decode_frame = &o_mp3_decode_frame;
    data->inf.data = _data;
    return data;
}

static void* Mp3Decoder_dtor(void* _data) {
    struct Mp3Decoder* data = _data;
    return data;
}

static void* Mp3Decoder_clone(const void* _data) {
    return create(Mp3Decoder);
}

static int Mp3Decoder_differ(const void* _data, const void* _other)
{
    const struct Mp3Decoder* data = _data;
    const struct Mp3Decoder* other = _other;
    
    if (data == other)
	return 0;
    else if (!other || other->meta != Mp3Decoder)
	return -1;
    else 
	return 1;
}

static int o_mp3_decode_frame(void* _data, int val) {
    struct Mp3Decoder* data = _data;
    data->times++;
    return val*val;
}

static const struct Meta _Mp3Decoder = {
    sizeof(struct Mp3Decoder),
    Mp3Decoder_ctor,
    Mp3Decoder_dtor,
    Mp3Decoder_clone,
    Mp3Decoder_differ,
};

const void* Mp3Decoder = &_Mp3Decoder;
