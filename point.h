#ifndef POINT_H
#define POINT_H

typedef struct {
    float xpos;
    float ypos;
    float xspeed;
    float yspeed;
} point;

void calcPointSpeed2(point a, point b);


#endif