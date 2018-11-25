#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "window.h"
void gl_loop(double deltaT);
void gl_init();

GLFWwindow* window;

void fpsTitle()
{
    static int count = 0;
    static double time = 0.0;
    static double curtime = 0.0;
    static char c[15];

    count++;
    curtime = glfwGetTime() - time;
    sprintf(c, "%.d fps", (int)((double)count / curtime + 0.5));
    count = 0;
    time = glfwGetTime();
    glfwSetWindowTitle(window, c);
}

void createWindow(int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, width, height);
}

void init()
{
    gl_init();
}

void loop()
{
    static double t = 0;
    static double deltaT;

    while (!glfwWindowShouldClose(window)) {
        gl_loop(deltaT);
        glfwSwapBuffers(window);
        deltaT = glfwGetTime() - t;
        glfwWaitEvents();
        t = glfwGetTime();
        //fpsTitle();
    }
}

void destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}