#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>

#include <stdio.h>

#include "window.h"
#include "shader.h"
#include "point.h"
extern int pause;
GLint position;
GLint color;
int clear = 1;
unsigned int count = 0;
point* points;

int main()
{
    createWindow(500, 500, "gravity sim");

    srand((unsigned) time(NULL));

    init();

    points = calloc(1000, sizeof(point));
    if (!points) {
        printf("calloc returned null");
        exit(1);
    }

    for(int i = -10 ; i < 10; i++){
        for (int j = -10 ; j < 10 ; j++) {
            points[count].sx = 20 * j;
            points[count].sy = 20 * i;
            points[count].r = 1;
            points[count].m = 1;
            count ++ ;
        }
    }

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
    color = glGetUniformLocation(program, "u_c");
    glUseProgram(program);

    glEnable(GL_PROGRAM_POINT_SIZE);
    
}
void gl_loop(double deltaT)
{
    if(clear)glClear(GL_COLOR_BUFFER_BIT);
    if (pause != 0) {
        collusion();
        calcForces();
        updateSpeed(deltaT);
        updateLocation(deltaT);
    }
    updateViewportCordinates();
    for (unsigned int i = 0; i < count; i++) {
        glPointSize((points[i].r/2)/view_factor);
        glUniform1f(color, points[i].m/1000+0.2);
        glUniform2f(position, points[i].glx, points[i].gly);
        glDrawArrays(GL_POINTS, 0, 1);
    }
}