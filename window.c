#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "window.h"
extern unsigned int count;
extern int G;
extern int clear;
int g;
void addpoint(double x, double y);
int ap;
void gl_loop(double deltaT);
void gl_init();

GLFWwindow* window;
int view_factor = 1;
int wx, wy;

int pause = 1;

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

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (ap) {
        glfwGetWindowSize(window, &wx, &wy);
        addpoint((xpos - wx / 2.0) * view_factor, (wy / 2.0 - ypos) * view_factor);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        glfwGetWindowSize(window, &wx, &wy);
        addpoint((x - wx / 2.0) * view_factor, (wy / 2.0 - y) * view_factor);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (!ap)
            ap = 1;
        else
            ap = 0;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (g) {
        G += yoffset * 1000;
        return;
    }
    if (yoffset > 0 && view_factor < 1024) {
        view_factor *= 2;
        return;
    }
    if (yoffset < 0 && view_factor != 1) {
        view_factor /= 2;
        return;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static int f = 0, w, h, px, py;

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        if (!f) {
            glfwGetWindowSize(window, &w, &h);
            glfwGetWindowPos(window, &px, &py);
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, 60);
            wx = 1920;
            wy = 1080;
            glViewport(0, 0, wx, wy);
            f = 1;
        } else {
            glfwSetWindowMonitor(window, NULL, px, py, w, h, GLFW_DONT_CARE);
            wx = w;
            wy = h;
            glViewport(0, 0, wx, wy);

            f = 0;
        }
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (pause)
            pause = 0;
        else
            pause = 1;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        printf("count = %d\n", count);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        count = 0;
    }
    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
        g = 1;
    } else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
        g = 0;
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        printf("%d\n", G);
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        if (clear == 0) clear = 1;
        else clear = 0;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glfwGetWindowSize(window, &wx, &wy);
    glViewport(0, 0, wx, wy);
}

void createWindow(int width, int height, const char* title)
{
    glfwInit();
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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
        glfwPollEvents();
        t = glfwGetTime();
        //fpsTitle();
    }
}

void destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}