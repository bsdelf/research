#include "Object.h"

size_t sizeOf(const void* _data) {
    const struct Meta* const* meta = _data;
    assert(_data && *meta);

    return (*meta)->size;
}

void* create(const void* _meta, ...) {
    const struct Meta* meta = _meta;
    void* data = calloc(1, meta->size);
    assert(data);

    *(const struct Meta**)data = meta;

    if (meta->ctor) {
	va_list args;
	va_start(args, _meta);
	data = meta->ctor(data, &args);
	va_end(args);
    }

    return data;
}

void release(void* _data) {
    const struct Meta** meta = _data;
    if (_data && *meta && (*meta)->dtor)
	_data = (*meta)->dtor(_data);
    free(_data);
}

void* clone(const void* _data) {
    const struct Meta* const* meta = _data;
    assert(_data && *meta && (*meta)->clone);
    return (*meta)->clone(_data);
}

int differ(const void* _data, const void* _other) {
    const struct Meta* const* meta = _data;
    assert(_data && *meta && (*meta)->differ);
    return (*meta)->differ(_data, _other);
}
