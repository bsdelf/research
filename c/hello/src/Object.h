#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

struct Class
{
    size_t size;
    void* (* ctor)(void* self, va_list* app);
    void* (* dtor)(void* self);
    void* (* clone)(const void* self);
    int (* differ)(const void* self, const void* b);
};

size_t sizeOf(const void* self);
void* new(const void* _class, ...);
void delete(void* self);
void* clone(const void* self);
int differ(const void* self, const void* b);

#endif
