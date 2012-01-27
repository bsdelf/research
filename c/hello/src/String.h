#ifndef String_h
#define String_h

#ifdef __cplusplus
extern "C" {
#endif

struct String
{
    const void* clazz;
    char* text;
};

extern const void* String;

#ifdef __cplusplus
}
#endif

#endif
