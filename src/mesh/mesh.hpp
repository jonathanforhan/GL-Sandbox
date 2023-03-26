#ifndef GLSANDBOX_MESH_HPP
#define GLSANDBOX_MESH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader/shader.hpp"
#include <vector>
#include <string>

#define MAX_BONE_INFLUENCE 4

namespace glsb {

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Tex {
    uint32_t id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex>   vertices;
    std::vector<uint32_t> indices;
    std::vector<Tex>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Tex> textures);
    void Draw(Shader &shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

} // glsb

#endif //GLSANDBOX_MESH_HPP
