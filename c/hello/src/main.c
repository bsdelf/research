#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "Object.h"
#include "String.h"

int 
main()
{
    /*
    struct point_t* a = NULL;
    struct point_t* b = NULL;
    char* text;

    a = point_create();
    a->x = 10;
    a->y = 10;

    b = point_create();
    b->x = 1;
    b->y = 1;

    point_addto(a, b);

    text = point_tostr(b);
    printf("point b: %s\n", text);
    free(text);
    
    point_release(a);
    point_release(b);

    */
    struct String* stra = new(String, "hello你好!");
    printf("String stra text: %s\n", stra->text);
    printf("string sizeof(stra): %d\n", sizeOf(stra));

    struct String* strb = clone(stra);
    printf("String text:%s\n", stra->text);

    delete(stra);
    delete(strb);

    return 0;
}
