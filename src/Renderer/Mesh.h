#pragma once
#include <vector>
#include <functional>
#include <Core/UUID.h>
#include "Vertex.h"

namespace FikoEngine {
    enum class MeshType {
        Cube,
        Quad,
        Triangle,
        Custom,
        None
    };

    static inline std::string MeshTypeToString(MeshType type) {
        switch (type) {
            case MeshType::Cube:
                return "Cube";
            case MeshType::Quad:
                return "Quad";
            case MeshType::Triangle:
                return "Triangle";
            case MeshType::Custom:
                return "Custom";
            case MeshType::None:
                return "None";
        }
        return "Unknown";
    }

    struct Mesh {
    public:
        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};
        UUID id;
    };
}
namespace std {
    template<>
    struct hash<FikoEngine::Mesh> {
        auto operator()(FikoEngine::Mesh const &m) const noexcept {
            return m.id;
        }
    };
}
