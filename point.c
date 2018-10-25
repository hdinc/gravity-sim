#include <math.h>
#include "point.h"

#define G 1

void addpoint(float x, float y)
{
    points[count].xpos = x;
    points[count].ypos = y;
    count++;
}