#ifndef GLSANDBOX_MESH_HPP
#define GLSANDBOX_MESH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <memory>
#include "texture.hpp"

namespace glsb {

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;

    Vertex()=default;

    Vertex(glm::vec3 pPos, glm::vec2 pTexCoords, glm::vec3 pNormal)
        : position(pPos), texCoords(pTexCoords), normal(pNormal) {};

    Vertex(glm::vec3 pPos, glm::vec2 pTexCoords)
        : position(pPos), texCoords(pTexCoords), normal(glm::vec3(0.0f, 0.0f, 0.0f)) {};
};

struct MeshEntry {
    ~MeshEntry() {
        if(VBO != 0) {
            glDeleteBuffers(1, &VBO);
        }
        if(EBO != 0) {
            glDeleteBuffers(1, &EBO);
        }
    }

    void init(const std::vector<Vertex>& pVertices, const std::vector<uint32_t>& pIndices) {
        numIndices = pIndices.size();
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (uint32_t)(sizeof(Vertex) * pVertices.size()), &pVertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (uint32_t)(sizeof(uint32_t) * numIndices), &pIndices[0], GL_STATIC_DRAW);
    }

    uint32_t VBO{}, EBO{};
    uint32_t numIndices = 0;
    uint32_t materialIndex = 0;
};


class Mesh {
public:
    bool loadMesh(const char* pFilename);

    void render();

private:
    bool initFromScene(const aiScene* pScene, const char* pFilename);
    void initMesh(uint32_t pIndex, const aiMesh* paiMesh);
    bool initMaterials(const aiScene* pScene, const char* pFilename);

    std::vector<MeshEntry> mEntries;
    std::vector<std::shared_ptr<Texture>> mTextures;
};

} // glsb

#endif //GLSANDBOX_MESH_HPP
