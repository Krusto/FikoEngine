#version 450 core

layout(location = 0) out vec4 FragColor;

layout(location = 0) in vec3 color;

layout(binding = 0) uniform sampler2D ourTexture;
void main()
{

    FragColor = vec4(color,1.0);
}