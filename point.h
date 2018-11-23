#ifndef POINT_H
#define POINT_H

typedef struct Point {
    double sx, sy;  //location
    double vx, vy;  //velocity
    double m;       //mass
    double fx, fy;  //force
    float glx, gly; //opengl viewport cordinates
    float r;        //radius

} point;

extern unsigned int count;
extern point* points;
extern int wx, wy;
extern int view_factor;

void collusion();
void addpoint(double x, double y);
void calcForces();
void updateSpeed(double timePassed);
void updateLocation(double timePassed);
void updateViewportCordinates();
void initPoints();

#endif