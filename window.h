#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

extern GLFWwindow* window;

void createWindow(int width, int height, const char* title);
void destroyWindow();
void loop();
void init();
#endif //WINDOW_H
