#version 450 core

layout(location = 0) out vec4 FragColor;

struct Material {
    float shininess;
}; 
  
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;
};

struct VertexData{
    vec3 vertNormal;
    vec2 texCoord;
    vec3 worldPos;
    vec3 viewPos;
};

layout(location = 0) in Material material;
layout(location = 4) in Light light;
layout(location = 9) in VertexData vertexData;

layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D specularTexture;
void main()
{

    vec3 ambient  =  light.ambient * vec3(texture(diffuseTexture, vertexData.texCoord));

    // diffuse 
  	vec3 norm = normalize(vertexData.vertNormal);
    vec3 lightDir = normalize(light.position - vertexData.worldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  =  light.diffuse * diff * vec3(texture(diffuseTexture, vertexData.texCoord));  
    
    // specular
    vec3 viewDir = normalize(vertexData.viewPos - vertexData.worldPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular =  light.specular * spec * (vec3(1.0) - vec3(texture(specularTexture,vertexData.texCoord)));  
        
    vec3 outColor =  light.intensity * (diffuse + specular + ambient);

    FragColor = vec4(outColor,1.0);
}