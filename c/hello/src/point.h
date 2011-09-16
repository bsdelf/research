#ifndef POINT_H
#define POINT_H

struct point_t 
{
    int x;
    int y;
};

struct point_t* point_create(void);
void point_release(struct point_t* point);
void point_addto(const struct point_t* from, struct point_t* to);
char* point_tostr(const struct point_t* point);

#endif
