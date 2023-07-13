#pragma once
#include <Renderer/Mesh.h>
#include <Renderer/Material.h>
//#include <assimp/scene.h>

namespace FikoEngine {
    struct Object {
        Mesh mesh;
        Material* material;
    };

    class ObjectLoader {
    public:
        static std::unordered_map<std::string, Object> Load(std::string Path, Material* material);

  //      static Object processMesh(Material* material, aiMesh *mesh, const aiScene *scene);

    //    static void processNode(Material* material, std::unordered_map<std::string, Object> &meshes, aiNode *node,
      //                          const aiScene *scene);

    private:
    };
}