#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 vcolor;

out vec3 fcolor;

void main()
{
    fcolor = vcolor;
    gl_Position = vec4(position, 0.0, 1.0); //sdsgsdgfsdgf; 
}