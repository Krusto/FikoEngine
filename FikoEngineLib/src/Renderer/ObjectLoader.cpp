#include "ObjectLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

namespace FikoEngine {
    /*Object ObjectLoader::processMesh(Material* material, aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.pos = vector;

            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoord = vec;
            } else {
                vertex.texCoord = glm::vec2(0.0f, 0.0f);
            }
            vertex.normal = glm::vec3();
            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial *materialai = scene->mMaterials[mesh->mMaterialIndex];
            Material* outMaterial = material;

            aiColor4D diffuse(0.f, 0.f, 0.f, 0.f);
            aiColor4D spec(0, 0, 0, 0);
            aiColor4D ambient(0, 0, 0, 0);
            aiGetMaterialColor(materialai, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
            aiGetMaterialColor(materialai, AI_MATKEY_COLOR_SPECULAR, &spec);
            aiGetMaterialColor(materialai, AI_MATKEY_COLOR_AMBIENT, &ambient);

            float specularExponent;
            materialai->Get(AI_MATKEY_SHININESS, specularExponent);
            outMaterial->Set("material.shininess", specularExponent);

            outMaterial->Set("material.diffuse", glm::vec3{diffuse.r, diffuse.g, diffuse.b});
            outMaterial->Set("material.specular", glm::vec3{spec.r, spec.g, spec.b});
            outMaterial->Set("material.ambient", glm::vec3{ambient.r, ambient.g, ambient.b});

            return Object{Mesh{vertices, indices}, outMaterial};
        }
        return Object{Mesh{vertices, indices}};
    }


    void
    ObjectLoader::processNode(Material* material, std::unordered_map<std::string, Object> &meshes, aiNode *node,
                              const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.try_emplace(std::string(mesh->mName.C_Str()), processMesh(material, mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(material, meshes, node->mChildren[i], scene);
        }

    }*/

    std::unordered_map<std::string, Object> ObjectLoader::Load(std::string Path, Material* material) {
        std::unordered_map<std::string, Object> output;

       /* Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(Path,
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_Triangulate
        );
        if (!scene) {
            std::cout << importer.GetErrorString() << '\n';
            return {};
        }

        processNode(material, output, scene->mRootNode, scene);
*/
        return output;
    }
}