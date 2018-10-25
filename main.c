#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "window.h"
#include "shader.h"

int main()
{
    createWindow(500, 500, "graphics pad");

    init();
    loop();

    destroyWindow();
}

void gl_init()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, +0.0f, +0.0f, +0.0f, +1.0f, 
        +0.0f, +1.0f, +0.0f, +0.0f, +0.0f, +1.0f, 
        +1.0f, -1.0f, +0.0f, +0.0f, +0.0f, +1.0f, 
        -1.0f, +1.0f, +0.5f, +0.0f, +1.0f, +0.0f, 
        +1.0f, +1.0f, +0.5f, +0.0f, +1.0f, +0.0f, 
        +0.0f, -1.0f, -0.5f, +0.0f, +1.0f, +0.0f
    };

    GLushort indices[] = {
        0, 1, 2,
        3, 4, 5
    };

    glClearColor(+0.0f, +0.0f, +0.0f, +1.0f);

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, 6 * 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));

    GLuint program = createShaderProgram("vertexShader.glsl", "fragmentShader.glsl");
    glUseProgram(program);

    glEnable(GL_DEPTH_TEST);
}

void gl_loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}