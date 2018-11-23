#include <math.h>
#include <stdio.h>
#include "point.h"
static void setForcesZero();

#define G 1000

void addpoint(double x, double y)
{
    points[count].sx = x;
    points[count].sy = y;
    points[count].vx = 0;
    points[count].vy = 0;
    points[count].m = 1;
    points[count].r = 2;
    count++;
}

void collusion()
{
    double dist;
    for (unsigned int i = 0; i < count; i++) {
        for (unsigned int j = i + 1; j < count; j++) {
            dist = sqrt((points[i].sx - points[j].sx) * (points[i].sx - points[j].sx) + (points[i].sy - points[j].sy) * (points[i].sy - points[j].sy));
            if (dist < points[i].r + points[j].r) {
                points[i].vx = (points[i].vx * points[i].m + points[j].vx * points[j].m) / (points[i].m + points[j].m);
                points[i].vy = (points[i].vy * points[i].m + points[j].vy * points[j].m) / (points[i].m + points[j].m);
                points[i].m += points[j].m;
                points[i].r = 2 * sqrt(points[i].m);
                points[j] = points[count - 1];
                count--;
                j--;
            }
        }
    }
}

void calcForces()
{
    setForcesZero();
    double xf, yf, factor, dist;
    for (unsigned int i = 0; i < count; i++) {
        for (unsigned int j = i + 1; j < count; j++) {
            dist = sqrt((points[i].sx - points[j].sx) * (points[i].sx - points[j].sx) + (points[i].sy - points[j].sy) * (points[i].sy - points[j].sy));
            factor = (G * points[i].m * points[j].m) / (dist * dist * dist);
            xf = factor * (points[i].sx - points[j].sx);
            yf = factor * (points[i].sy - points[j].sy);
            points[j].fx += xf;
            points[j].fy += yf;
            points[i].fx -= xf;
            points[i].fy -= yf;
        }
        //test
        // points[i].fx = 1;
        // points[i].fy = 1;
    }
}

void updateSpeed(double timePassed)
{
    for (unsigned int i = 0; i < count; i++) {
        points[i].vx += (points[i].fx / points[i].m) * timePassed;
        points[i].vy += points[i].fy / points[i].m * timePassed;
    }
}

void updateLocation(double timePassed)
{
    for (unsigned int i = 0; i < count; i++) {
        points[i].sx += points[i].vx * timePassed;
        points[i].sy += points[i].vy * timePassed;
    }
}

void updateViewportCordinates()
{
    for (unsigned int i = 0; i < count; i++) {
        points[i].gly = (points[i].sy * 2) / (view_factor * wy);
        points[i].glx = (points[i].sx * 2) / (view_factor * wx);
    }
}

static void setForcesZero()
{
    for (unsigned int i = 0; i < count; i++) {
        points[i].fx = 0.0;
        points[i].fy = 0.0;
    }
}

void initPoints() //you can use calloc to set zero all;
{
    for (int i = 0; i < count; i++) {
        points[i].vx = 0.0;
        points[i].vy = 0.0;
    }
}
