#include "point.h"
#include <stdio.h>
#include <stdlib.h>

struct point_t* 
point_create(void)
{
    struct point_t* point = NULL;
    point = (struct point_t*)malloc(sizeof(struct point_t));
    point->x = 0;
    point->y = 0;
    return point;
}

void 
point_release(struct point_t* point)
{
    free(point);
}

void 
point_addto(const struct point_t* from, struct point_t* to)
{
    to->x += from->x;
    to->y += from->x;
}

char* 
point_tostr(const struct point_t* point)
{
    const char* format = "(%d, %d)";
    char* str = NULL;
    int size = 0; 

    size = snprintf(NULL, 0, format, point->x, point->y) + 1; 
    str = (char*)malloc(size);
    snprintf(str, size, format, point->x, point->y); 

    return str;
}
