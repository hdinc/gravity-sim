#version 330 core
out vec4 fcolor;
uniform vec2 u_position;
uniform float u_radius;

struct iresolution{
    float x;
    float y;
};

void main() {
    struct iresolution iResolution;
    iResolution.x = 500;
    iResolution.y = 500;
    // the center of the texture
    //vec2 center = vec2(iResolution.x/2.0,iResolution.y/2.0); 
	
    // current pixel location
    vec2 loc = gl_FragCoord.xy;
	
    // how far we are from the center
    float radius=length(loc-u_position);
	
    // if we are within our circle, paint it red
    if (radius<u_radius)
        fcolor = vec4(1,0,0,1); // red
    else
        fcolor = vec4(0,0,0,1); // black
}