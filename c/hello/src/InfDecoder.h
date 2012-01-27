#ifndef InfDecoder_h
#define InfDecoder_h

#include <stdlib.h>
#define MALLOC(type) (type*)malloc(sizeof(type))
#define FREE(ptr) free(ptr)

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Vfn)(void);

struct InfTable {
    Vfn vfn;
};

struct InfDecoder {
    void (**vtable)(void);
};

typedef int (*fn_decode_frame)(void*, int);
typedef int (*fn_get_times)(void*);

#define inf_decode_frame(thiz, val) \
    ((fn_decode_frame)(thiz->vtable[0]))(thiz, val)
    //((fn_decode_frame)(thiz->itbl[0].vfn))(thiz, val)

#define inf_get_times(thiz) \
    ((fn_get_times)(thiz->vtable[1]))(thiz)
    //((fn_get_times)(thiz->itbl[1].vfn))(thiz)

#ifdef __cplusplus
}
#endif

#endif
