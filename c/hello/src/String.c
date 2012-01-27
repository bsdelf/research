#include "String.h"
#include "Object.h"
#include <string.h>

//static void init(struct String* self);

static void* String_ctor(void* _self, va_list* app)
{
    struct String* self = _self;
    //init(self);
    const char* text = va_arg(*app, const char*);

    self->text = malloc(strlen(text)+1);
    assert(self->text);
    strcpy(self->text, text);
    return self;
}

static void* String_dtor(void* _self)
{
    struct String* self = _self;
    free(self->text);
    self->text = NULL;
    return self;
}

static void* String_clone(const void* _self)
{
    const struct String* self = _self;
    return create(String, self->text);
}

static int String_differ(const void* _self, const void* _b)
{
    const struct String* self = _self;
    const struct String* b = _b;
    
    if (self == b)
	return 0;
    if (!b || b->clazz != String)
	return 1;
    return strcmp(self->text, b->text);
}

static const struct Meta _String =
{
    sizeof(struct String),
    String_ctor, 
    String_dtor,
    String_clone,
    String_differ
};

const void* String = &_String;

/*
static void init(struct String* self)
{
    self->clazz = &_String;
}
*/
