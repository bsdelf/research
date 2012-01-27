#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Meta {
    size_t size;
    void* (*ctor)(void* _data, va_list* args);
    void* (*dtor)(void* _data);
    void* (*clone)(const void* _data);
    int (*differ)(const void* _data, const void* _other);
};

size_t sizeOf(const void* _data);
void* create(const void* _meta, ...);
void release(void* _data);
void* clone(const void* _data);
int differ(const void* _data, const void* _other);

#ifdef __cplusplus
}
#endif

#endif
