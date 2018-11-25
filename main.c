#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "window.h"
#include "shader.h"

GLint u_cpos;
GLint u_r;

float radius=5.0;

GLfloat vertices[8] = {
    -1.0f, +1.0f,
    +1.0f, +1.0f,
    +1.0f, -1.0f,
    -1.0f, -1.0f
};

GLubyte indices[6] = { 0, 1, 2, 0, 3, 2 };

int main()
{
    createWindow(500, 500, "gravity sim");
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    init();

    loop();

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
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

    GLuint ibID;
    glGenBuffers(1, &ibID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    GLuint program = createShaderProgram("vertexShader.glsl", "fragmentShader.glsl");
    glUseProgram(program);

    u_cpos = glGetUniformLocation(program, "u_position");
    u_r = glGetUniformLocation(program, "u_radius");
    glClearColor(0.0,0.0,0.0,1.0);

}

void gl_loop(double deltaT)
{
    static double wx,wy;
    glClear(GL_COLOR_BUFFER_BIT);
    glfwGetCursorPos(window,&wx, &wy);
    glUniform2f(u_cpos,wx,500-wy);
    glUniform1f(u_r, radius);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    radius+=yoffset/2.0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
}