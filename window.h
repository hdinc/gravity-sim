#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

void fpsTitle();
void createWindow(int width, int height, const char* title);
void destroyWindow();
void startLoop();
#endif //WINDOW_H
