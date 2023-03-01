#include "Renderer/MeshBuilder.h"

namespace FikoEngine {
    Mesh MeshBuilder::CreateTriangle()
    {
        Mesh output;

        output.vertices = std::vector<Vertex>({
<<<<<<< HEAD
                                                      Vertex{glm::vec3{-0.5,-0.5,0},glm::vec3{0,1,0},glm::vec2{0,0} },
                                                      Vertex{glm::vec3{ 0.5, 0,0},glm::vec3{0,1,0},glm::vec2{0,0} },
                                                      Vertex{glm::vec3{ 0.5,-0.5,0},glm::vec3{0,1,0},glm::vec2{0,0} }
=======
                                                      Vertex{glm::vec3{-0.5, -0.5, 0}, glm::vec3{0, 1, 0}}, //glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{ 0.5,    0, 0}, glm::vec3{0, 1, 0}}, //glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{ 0.5, -0.5, 0}, glm::vec3{0, 1, 0}}, //glm::vec2{0, 0}}
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
                                              });
        output.indices = { 2,3,0 };

        return output;
    }

    Mesh MeshBuilder::CreateQuad()
    {
        Mesh output;

        output.vertices = std::vector<Vertex>({
<<<<<<< HEAD
                                                      Vertex{glm::vec3{-0.5,-0.5,0},glm::vec3{0,1,0},glm::vec2{0,0} },
                                                      Vertex{glm::vec3{-0.5, 0.5,0},glm::vec3{0,1,0},glm::vec2{0,1} },
                                                      Vertex{glm::vec3{ 0.5, 0.5,0},glm::vec3{0,1,0},glm::vec2{1,1} },
                                                      Vertex{glm::vec3{ 0.5,-0.5,0},glm::vec3{0,1,0},glm::vec2{1,0} }
=======
                                                      Vertex{glm::vec3{-0.5, -0.5, 0}, glm::vec3{0, 1, 0}},//,glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{-0.5,  0.5, 0}, glm::vec3{0, 1, 0}},//glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{ 0.5,  0.5, 0}, glm::vec3{0, 1, 0}},//glm::vec2{0, 0}},
                                                      Vertex{glm::vec3{ 0.5, -0.5, 0}, glm::vec3{0, 1, 0}},//glm::vec2{0, 0}}
>>>>>>> 4336de227144d7684ff5a4dc60e689d80c1bb650
                                              });
        output.indices = { 0,1,2,2,3,0 };

        return output;
    }

    Mesh MeshBuilder::CreateCube()
    {
        Mesh output;

        output.vertices = std::vector<Vertex>({

                                                      // positions                        // normals           // texture coords
                                                      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),glm::vec2(0.0f,  0.0f)},
                                                      Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),glm::vec2(0.0f,  1.0f)},
                                                      Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),glm::vec2(1.0f,  1.0f)},
                                                      Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),glm::vec2(1.0f,  0.0f)},

                                                      Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f,  1.0f),glm::vec2(0.0f,  0.0f)},
                                                      Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f,  1.0f),glm::vec2(0.0f,  1.0f)},
                                                      Vertex{glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f,  1.0f),glm::vec2(1.0f,  1.0f)},
                                                      Vertex{glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f,  1.0f),glm::vec2(1.0f,  0.0f)},

                                                      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), -glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(0.0f,  1.0f)},
                                                      Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), -glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(0.0f,  0.0f)},
                                                      Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), -glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(1.0f,  0.0f)},
                                                      Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), -glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(1.0f,  1.0f)},

                                                      Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(0.0f,  1.0f)},
                                                      Vertex{glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(0.0f,  0.0f)},
                                                      Vertex{glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(1.0f,  0.0f)},
                                                      Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),glm::vec2(1.0f,  1.0f)},

                                                      Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),glm::vec2(0.0f,  1.0f)},
                                                      Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),glm::vec2(0.0f,  0.0f)},
                                                      Vertex{glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),glm::vec2(1.0f,  0.0f)},
                                                      Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),glm::vec2(1.0f,  1.0f)},

                                                      Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),glm::vec2(0.0f,  1.0f)},
                                                      Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),glm::vec2(0.0f,  0.0f)},
                                                      Vertex{glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),glm::vec2(1.0f,  0.0f)},
                                                      Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),glm::vec2(1.0f,  1.0f)},
                                              });

        output.indices = { 0  ,1  ,2  ,2  ,3  ,0 ,
                           4  ,5  ,6  ,6  ,7  ,4 ,
                           8  ,9  ,10 ,10 ,11 ,8 ,
                           12 ,13 ,14 ,14 ,15 ,12,
                           16 ,17 ,18 ,18 ,19 ,16,
                           20 ,21 ,22 ,22 ,23 ,20};


        return output;
    }

    Mesh MeshBuilder::CreateMesh(MeshType type)
    {
        switch (type) {
            case MeshType::Quad:
                return MeshBuilder::CreateQuad();
            case MeshType::Triangle:
                return MeshBuilder::CreateTriangle();
            case MeshType::Cube:
                return MeshBuilder::CreateCube();
        }

        return {};
    }
}