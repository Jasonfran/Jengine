#version 330 core

in vec3 normal;

out vec4 FragColour;
uniform vec3 colour;

void main(){
    vec3 sun = vec3(1.0, 1.0, 1.0);
    float litAmount = max(dot(normal, sun), 0.1);
    FragColour = vec4(colour * litAmount, 1.0);
}