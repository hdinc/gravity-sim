#version 330 core
out vec4 color;
uniform float u_c;
void main()
{
    color = vec4(u_c,1.0-u_c,0.0,1.0);
}