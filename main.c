#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "window.h"
#include "shader.h"

static const float positions[] = {
    0.00f, 0.50f, //v0
    0.25f, 0.25f, //v1
    0.50f, 0.00f, //v2
    0.25f, -0.25f, //v3
    0.00f, -0.50f, //v4
    -0.25f, -0.25f, //v5
    -0.50f, 0.00f, //v6
    -0.25f, 0.25f //v7
};

static const unsigned int indices[] = {
    0, 7, 1,
    7, 6, 5,
    5, 4, 3,
    3, 2, 1
};

int main()
{
    createWindow(500, 500, "");

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID); //dfgsdfg
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    GLuint indexbufer;
    glGenBuffers(1, &indexbufer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 4 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint shader = createShaderProgram("vertexShader.glsl", "fragmentShader.glsl");
    

    GLint uniformid = glGetUniformLocation(shader, "u_barzo");
    glUseProgram(shader);
    glUniform4f(uniformid, 0.0f,0.8f,0.2f,1.0f);

    startLoop();

    destroyWindow();
}
void loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL);
}