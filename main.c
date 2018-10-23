#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "window.h"
#include "shader.h"

void gl_init();

int main()
{
    createWindow(500, 500, "graphics pad");

    init();
    loop();

    destroyWindow();
}

void gl_loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL);
}

void gl_init()
{
    glClearColor(+1.0f, +0.0f, +0.3f, +1.0f);
}