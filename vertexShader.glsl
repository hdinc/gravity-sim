#version 330 core

uniform vec3 position;

void main()
{
    gl_Position = vec4(position,1.0); 
}