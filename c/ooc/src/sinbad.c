#include "sinbad.h"

const struct SCVtbl SinbadVtbl[] = {
    {
	0, 0, (SCVfn)SinbadTurn
    },
    {
	0, 0, (SCVfn)SinbadMove
    }
};

void SinbadIni(struct Sinbad* thiz, const char* name) {
    thiz->vtbl = SinbadVtbl;
    thiz->name = name;
    thiz->rad = 0;
    thiz->x = 0;
    thiz->y = 0;
}

void SinbadFin(struct Sinbad* thiz) {

}

void SinbadTurn(struct Sinbad* thiz, double rad) {
    thiz->rad += rad;
    printf("SinbadTurn %s : %f\n", thiz->name, thiz->rad);
}

void SinbadMove(struct Sinbad* thiz, double dis) {
    thiz->x += dis*cos(thiz->rad);
    thiz->y += dis*sin(thiz->rad);
    printf("SinbadMove %s : (%f, %f)\n", thiz->name, thiz->x, thiz->y);
}

void SinbadJump(struct Sinbad* thiz) {

}

int SinbadAttack(struct Sinbad* thiz, struct IRole* role) {
    return 0;
}
