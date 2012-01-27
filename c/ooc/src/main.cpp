#include <iostream>
using namespace std;

#include "sinbad.h"

double a2r(double a) {
    return a/360*2*3.1415926;
}

int main() {
    struct Sinbad s1, s2;
    SinbadIni(&s1, "s1");
    SinbadIni(&s2, "s2");

    struct IRole* role;
    role = (struct IRole*)&s1;

    IRoleTurn(role, a2r(60));
    IRoleMove(role, 10);
    IRoleTurn(role, a2r(-60));
    IRoleMove(role, 10);

    IRoleMove(&s2, 10);

    return 0;
}
