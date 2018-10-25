#ifndef POINT_H
#define POINT_H

typedef struct {
    float xpos;
    float ypos;
} point;

extern int count;
extern point* points;

void addpoint(float x, float y);

#endif