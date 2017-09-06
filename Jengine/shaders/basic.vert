#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

uniform mat4 MVP;
uniform mat4 model;

out vec3 normal;
out vec2 texCoords;

void main(){
    gl_Position = MVP * vec4(Position, 1.0);
    normal = normalize(transpose(inverse(mat3(model))) * Normal);
    texCoords = TexCoords;
}