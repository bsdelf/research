#include <stdio.h>

void overflow()
{
    int* ret;
    ret = (char*)&ret+2;
    (*ret) += 8;
}

void main()
{
    int x = 9;
    overflow();
    x = 10;
    printf("%d\n", x);
    printf("%d\n", sizeof(char));
}
