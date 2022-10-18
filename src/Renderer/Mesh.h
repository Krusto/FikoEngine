#pragma once
#include <vector>
#include <Core/UUID.h>
#include "Vertex.h"

enum class MeshType {
    Quad,
    Triangle,
    Custom,
    None
};

static inline std::string MeshTypeToString(MeshType type) {
    switch (type) {
    case MeshType:: Quad:
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

struct Mesh{
public:
    std::vector<Vertex> vertices{};
    std::vector<uint32_t> indices{};
    UUID id;
};
namespace std
{
    template<> struct hash<Mesh>
    {
        auto operator()(Mesh const& m) const noexcept
        {
            return m.id;
        }
    };
}
struct Mesh2D {
public:
    std::vector<Vertex2D> vertices{};
    std::vector<uint32_t> indices{};
    UUID id = 0;
};
namespace std
{
    template<> struct hash<Mesh2D>
    {
        auto operator()(Mesh2D const& m) const noexcept
        {
            return m.id;
        }
    };
}
