#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "window.h"
#include "shader.h"
#include "point.h"

GLint position;
int count = 0;
point* points;

int main()
{
    createWindow(500, 500, "graphics pad");

    init();

    points = malloc(50 * sizeof(point));

    loop();

    destroyWindow();
}

void gl_init()
{

    glClearColor(+0.0f, +0.0f, +0.0f, +1.0f);

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vbID;
    //glGenBuffers(1, &vbID);
    //glBindBuffer(GL_ARRAY_BUFFER, vbID);

    GLuint program = createShaderProgram("vertexShader.glsl", "fragmentShader.glsl");

    position = glGetUniformLocation(program, "u_position");
    glUseProgram(program);
}

void gl_loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < count; i++) {
        glUniform2f(position, points[i].xpos, points[i].ypos);
        glDrawArrays(GL_POINTS, 0,1);
    }
}