#pragma once
#include <Renderer/Mesh.h>

class MeshBuilder {
public:
    static Mesh CreateMesh(MeshType type);
private:
    static Mesh CreateTriangle();
    static Mesh CreateQuad();
};