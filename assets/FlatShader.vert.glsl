#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

struct Camera{
    mat4 projection;
    mat4 view;
    mat4 model;
};

uniform vec3 color;
uniform Camera camera;

layout(location = 0) out vec3 outColor;

void main()
{
    
    outColor = color;

    vec3 worldPos = vec3(camera.model *vec4(aPosition,1.0));

    gl_Position = camera.projection * camera.view * vec4(worldPos,1.0);

}