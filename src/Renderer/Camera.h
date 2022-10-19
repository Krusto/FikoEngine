#pragma once
#include <cstdint>
#include <string_view>
#include <glad/glad.h>
#include <Core/Ref.h>
#include <Renderer/Viewport.h>
#include <Renderer/Shader.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

struct CameraSpec {
public:
    CameraSpec() = default;
    CameraSpec(ViewportSize size, float FOV, float Near = 0.1f, float Far = 1000.0f) {
        this->viewport = size;
        this->fov = FOV;
        this->Near = Near;
        this->Far = Far;
        this->AspectRatio = (float)size.width/(float)size.height;
    }
    ViewportSize viewport{0,0};
    float fov{};
    float Near = 0.1f;
    float Far = 1000.0f;
    float AspectRatio = 1.0f;
};

class Camera :public  RefCounted {
public:
    Camera() = default;
    Camera(CameraSpec spec);

    void ChangeViewport(uint32_t width,uint32_t height);
    void Update();
    const auto& GetView() const { return this->m_View; }
    auto& GetView() { return this->m_View; }
    const auto& GetProjection() const { return this->m_Projection; }
    auto& GetProjection() { return this->m_Projection; }

    void SetPosition(glm::vec3 position) { this->m_Position = position; }
    void SetRotation(glm::vec3 rotation) { this->m_Rotation = rotation; }
    const glm::vec3& GetPosition() const { return this->m_Position; }
    glm::vec3& GetPosition()  { return this->m_Position; }
    const glm::vec3& GetRotation() const { return this->m_Rotation; }
    glm::vec3& GetRotation() { return this->m_Rotation; }

    void Move(glm::vec3 dir);
    void Rotate(glm::vec3 rot);
    void Upload(Ref<Shader> shader,std::string_view uProjection = "u_Projection", std::string_view uView = "u_View");

    glm::vec3 GetVectorUP(){return m_VectorUP;}
    glm::vec3 GetVectorForward(){return m_VectorForward;}

    CameraSpec& GetSpec(){return m_CameraSpec;}

    void ProcessMouseMovement(float xoffset, float yoffset,float dt, bool constrainPitch = true);
    void ProcessKeyboardInput(int action, int key,float dt);
private:
    glm::vec3 m_VectorUP{};
    glm::vec3 m_VectorForward{};
    glm::vec3 m_Position{};
    glm::vec3 m_Rotation{};

    glm::mat4 m_Projection{};
    glm::mat4 m_View{};

    CameraSpec m_CameraSpec{};

    bool startedEvent{};
    glm::vec3 m_MoveVector{};
    glm::vec3 m_RotateVector{};
};