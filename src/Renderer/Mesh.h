#pragma once
#include <vector>
#include <functional>
#include <Core/UUID.h>
#include "Vertex.h"

namespace FikoEngine {
    enum class MeshType {
        Quad,
        Triangle,
        Custom,
        None
    };

    static inline std::string MeshTypeToString(MeshType type) {
        switch (type) {
            case MeshType::Quad:
                return "Quad";
                break;
            case MeshType::Triangle:
                return "Triangle";
                break;
            case MeshType::Custom:
                return "Custom";
                break;
            case MeshType::None:
                return "None";
                break;
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
