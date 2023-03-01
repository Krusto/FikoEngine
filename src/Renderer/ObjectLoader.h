#pragma once
#include <Renderer/Mesh.h>
#include <Renderer/Material.h>
#include <assimp/scene.h>

struct Object {
public:
    Mesh mesh;
    Ref<Material> material;
};

class ObjectLoader {
public:
    static std::unordered_map<std::string,Object> Load(std::string Path,Ref<Material> material);

    static Object processMesh(Ref<Material> material, aiMesh* mesh, const aiScene* scene);
    static void processNode(Ref<Material> material,std::unordered_map<std::string, Object>& meshes,aiNode* node, const aiScene* scene);
private:
};