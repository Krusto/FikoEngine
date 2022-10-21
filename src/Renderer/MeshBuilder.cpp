#include "Renderer/MeshBuilder.h"

namespace FikoEngine {
    Mesh MeshBuilder::CreateTriangle() {
        Mesh output;

        output.vertices = std::vector<Vertex>({
                                                      Vertex{glm::vec3{-0.5, -0.5, 0}, glm::vec3{0, 1, 0},
                                                             glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{0.5, 0, 0}, glm::vec3{0, 1, 0}, glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{0.5, -0.5, 0}, glm::vec3{0, 1, 0},
                                                             glm::vec2{0, 0}}
                                              });
        output.indices = {2, 3, 0};

        return output;
    }

    Mesh MeshBuilder::CreateQuad() {
        Mesh output;

        output.vertices = std::vector<Vertex>({
                                                      Vertex{glm::vec3{-0.5, -0.5, 0}, glm::vec3{0, 1, 0},
                                                             glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{-0.5, 0.5, 0}, glm::vec3{0, 1, 0},
                                                             glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{0.5, 0.5, 0}, glm::vec3{0, 1, 0},
                                                             glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{0.5, -0.5, 0}, glm::vec3{0, 1, 0},
                                                             glm::vec2{0, 0}}
                                              });
        output.indices = {0, 1, 2, 2, 3, 0};

        return output;
    }

    Mesh MeshBuilder::CreateMesh(MeshType type) {
        switch (type) {
            case MeshType::Quad:
                return MeshBuilder::CreateQuad();
                break;
            case MeshType::Triangle:
                return MeshBuilder::CreateTriangle();
        }
        return {};
    }
}