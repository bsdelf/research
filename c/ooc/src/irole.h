#ifndef IROLE_H
#define IROLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vtbl.h"

#ifdef __cplusplus
extern "C" {
#endif

enum IRoleInfEm {
    IRoleTurn,
    IRoleMove,
    IRoleJump,
    IRoleAttack
};

struct IRole {
    const struct SCVtbl* vtbl;
};

#ifdef __cplusplus
}
#endif

typedef void (*FnIRoleTurn)(void* thiz, double rad);
#define IRoleTurn(thiz, angle)	\
    ((FnIRoleTurn)((thiz)->vtbl[IRoleTurn].vfn))(thiz, angle)

typedef void (*FnIRoleMove)(void* thiz, double dis);
#define IRoleMove(thiz, dis)	\
    ((FnIRoleMove)((thiz)->vtbl[IRoleMove].vfn))(thiz, dis)

#endif
