#version 330 core
layout (location = 0) in vec2 P;
void main()
{
    gl_Position = vec4(P,0.5,1.0);
}