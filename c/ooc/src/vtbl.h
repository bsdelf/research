#ifndef SC_VTBL_H
#define SC_VTBL_H

#define talloc(type)	\
    (type*) malloc(sizeof(type))

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*SCFnIni)(void* thiz);
typedef void (*SCFnFin)(void* thiz);

typedef void (*SCVfn)(void);

struct SCVtbl {
    int d;
    int i;
    SCVfn vfn;
};

#ifdef __cplusplus
}
#endif

#endif
