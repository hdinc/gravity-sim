#include <glad/glad.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shader.h"

static GLuint complieShader(GLenum type, const char* shaderSource);
static char* getShader(const char* filename);

static void checkError(GLuint id, GLenum pname)
{
    int result;
    if (pname == GL_COMPILE_STATUS) {
        glGetShaderiv(id, pname, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = alloca(length);
            glGetShaderInfoLog(id, length, &length, message);
            printf("Failed to complie %s shader ; \n", (pname == GL_VERTEX_SHADER ? "vertex" : "fragment"));
            printf("%s\n", message);
            glDeleteShader(id);
            exit(-1);
        }
    } else if (pname == GL_LINK_STATUS || pname == GL_VALIDATE_STATUS) {
        glGetProgramiv(id, pname, &result);
        if (result == GL_FALSE) {
            int length;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = alloca(length);
            glGetProgramInfoLog(id, length, &length, message);
            printf("Failed to %s program;\n%s\n", pname == GL_LINK_STATUS ? "link" : "validate", message);
            glDeleteProgram(id);
            exit(-1);
        }
    }
}

GLuint createShaderProgram(const char* vsn, const char* fsn)
{
    char* vertexShader = getShader(vsn);
    char* fragmentShader = getShader(fsn);
    GLuint shaderProgram = glCreateProgram();
    GLuint vs = complieShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = complieShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    checkError(shaderProgram, GL_LINK_STATUS);
    glValidateProgram(shaderProgram);
    checkError(shaderProgram, GL_VALIDATE_STATUS);

    free(vertexShader);
    free(fragmentShader);

    glDeleteShader(fs);
    glDeleteShader(vs);

    return shaderProgram;
}

static GLuint complieShader(GLenum type, const char* shaderSource)
{
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &shaderSource, NULL);
    glCompileShader(id);
    checkError(id, GL_COMPILE_STATUS);
    return id;
}

static char* getShader(const char* filename)
{
    char* buffer = 0;
    long length;
    FILE* f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);
    fread(buffer, 1, length, f);
    fclose(f);
    buffer[length] = '\0';
    return buffer;
}
