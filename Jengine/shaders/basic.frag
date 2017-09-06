#version 330 core


struct DirLight{
    vec3 colour;
    vec3 direction;
};


in vec3 normal;

out vec4 FragColour;
uniform vec3 colour;
uniform DirLight directionalLights[10];

// basic diffuse lighting
vec3 calcDirLight(DirLight light, vec3 normal){
    float diffuse = max(dot(normal, light.direction), 0.0);
    return colour * light.colour * diffuse;
}

void main(){
    vec3 lightingResult;
    for(int i = 0; i < 10; i++)
        lightingResult += calcDirLight(directionalLights[i], normal);
    
    FragColour = vec4(lightingResult, 1.0f);
}