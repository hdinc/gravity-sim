#version 330 core
in vec4 vertexColor; // name must match with vertexshaders out
out vec4 color;
void main()
{
    color = vertexColor;
}