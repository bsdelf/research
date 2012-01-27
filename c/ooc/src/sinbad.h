#ifndef SINBAD_H
#define SINBAD_H

#include "irole.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Sinbad {
    const struct SCVtbl* vtbl;
    const char* name;
    double rad;
    double x;
    double y;
};

extern const struct SCVtbl SinbadVtbl[];

void SinbadIni(struct Sinbad* thiz, const char* name);
void SinbadFin(struct Sinbad* thiz);

void SinbadTurn(struct Sinbad* thiz, double rad);
void SinbadMove(struct Sinbad* thiz, double dis);
void SinbadJump(struct Sinbad* thiz);
int SinbadAttack(struct Sinbad* thiz, struct IRole* role);

#ifdef __cplusplus
}
#endif

#endif
