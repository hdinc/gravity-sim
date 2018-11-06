#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "window.h"
#include "shader.h"
#include "point.h"
extern int pause;
GLint position;
unsigned int count = 0;
point* points;

int main()
{
    createWindow(500, 500, "gravity sim");

    init();

    points = calloc(100, sizeof(point));
    printf("%p", points);

    loop();

    free(points);
    destroyWindow();
}

void gl_init()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vbID;
    glGenBuffers(1, &vbID);
    glBindBuffer(GL_ARRAY_BUFFER, vbID);

    GLuint program = createShaderProgram("vertexShader.glsl", "fragmentShader.glsl");
    position = glGetUniformLocation(program, "u_position");
    glUseProgram(program);
}
void gl_loop(double deltaT)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (pause != 0) {
        calcForces();
        updateSpeed(deltaT);
        updateLocation(deltaT);
    }
    updateViewportCordinates();
    for (unsigned int i = 0; i < count; i++) {
        glUniform2f(position, points[i].glx, points[i].gly);
        glDrawArrays(GL_POINTS, 0, 1);
    }
}