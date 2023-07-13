#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, float intensity, glm::vec3 rotation, LightType type)
{
	m_Type = type;
	m_Intensity = intensity;
	m_Color = color;
	m_Rotation = rotation;
	m_Position = position;
}
