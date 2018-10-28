#ifndef POINT_H
#define POINT_H

typedef struct {
    double sx, sy;
    double fx, fy;
    double vx, vy;
    float glx, gly; //opengl viewport cordinates
} point;

extern unsigned int count;
extern point* points;
extern int wx, wy;
extern int view_factor;

void addpoint(double x, double y);
void calcForces();
void updateSpeed(double timePassed);
void updateLocation(double timePassed);
void updateViewportCordinates();
void initPoints();

#endif