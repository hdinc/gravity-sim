#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

GLuint createShaderProgram(const char* vertexShader,const char* fragmentShader);
static GLuint complieShader(GLenum type, const char* shaderSource);
static char* getShader(const char* filename);

#endif