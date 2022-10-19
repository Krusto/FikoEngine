#pragma once
#include <Renderer/Mesh.h>

namespace FikoEngine {
    class MeshBuilder {
    public:
        static Mesh CreateMesh(MeshType type);

    private:
        static Mesh CreateTriangle();

        static Mesh CreateQuad();
    };
}