#version 330 core

out vec4 vertexColor;
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 vcolor;

void main()
{
    vertexColor = vec4(vcolor,1.0);
    gl_Position = vec4(position,0.0,1.0); 
}