#pragma once
#include <glm/glm.hpp>
enum LightType {
Point = 0,
Directional = 1,
Spotlight = 2,
Ambient = 3,
};

class Light {
public:
	Light() = default;
	Light(glm::vec3 position,glm::vec3 color,float intensity,glm::vec3 rotation,LightType type);
	static Light Create(glm::vec3 position, glm::vec3 color, float intensity, glm::vec3 rotation, LightType type) { return { position,color,intensity,rotation,type }; }
	auto GetPosition() const { return m_Position; }
	auto& GetPosition() { return m_Position; }
	void SetPosition(glm::vec3 position) { m_Position = position; }

	auto GetRotation() const { return m_Rotation; }
	auto& GetRotation() { return m_Rotation; }
	void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }

	auto GetColor() const{ return m_Color; }
	auto& GetColor() { return m_Color; }
	void SetColor(glm::vec3 color) { m_Color = color; }

	auto GetIntensity() const { return m_Intensity; }
	auto& GetIntensity() { return m_Intensity; }
	void SetIntensity(float intensity) { m_Intensity = intensity; }

	void Move(glm::vec3 d) { m_Position += d; }
	void Rotate(glm::vec3 d) { m_Rotation += d; }
	void IncreaseIntensity(float i) { m_Intensity += i; }
	void DecreaseIntensity(float i) { m_Intensity -= i; }

	auto GetType() const { return m_Type; }
	auto& GetType() { return m_Type; }
	void SetType(LightType type) { m_Type = type; }

private:
	LightType m_Type;
	glm::vec3 m_Position{};
	glm::vec3 m_Rotation{};
	glm::vec3 m_Color;
	float m_Intensity;
};