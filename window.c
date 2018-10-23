#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "window.h"

void gl_loop();
void gl_init();
int w;
int h;

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static int f = 0, w, h, px, py;

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        if(!f){
            glfwGetWindowSize(window, &w, &h);
            glfwGetWindowPos(window, &px, &py);
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, 60);
            glViewport(0, 0, 1920, 1080);
            f=1;
        }
        else {
            glfwSetWindowMonitor(window, NULL, px, py, w, h, GLFW_DONT_CARE);
            glViewport(0, 0, w, h);
            f=0;
        }
        
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void createWindow(int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    //glfwSetWindowAspectRatio(window,16,9);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void init()
{
    gl_init();
}

void loop()
{
    while (!glfwWindowShouldClose(window)) {
        gl_loop();
        glfwSwapBuffers(window);
        glfwPollEvents();
        //fpsTitle();
    }
}

void destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}