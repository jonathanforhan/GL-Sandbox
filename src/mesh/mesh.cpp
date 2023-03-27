#include <iostream>
#include "mesh.hpp"

const int ASSIMP_LOAD_FLAGS = (
    aiProcess_Triangulate |
    aiProcess_JoinIdenticalVertices |
    aiProcess_GenUVCoords |
    aiProcess_SortByPType |
    aiProcess_RemoveRedundantMaterials |
    aiProcess_FindInvalidData |
    //aiProcess_FlipUVs |
    aiProcess_CalcTangentSpace |
    aiProcess_GenSmoothNormals |
    aiProcess_ImproveCacheLocality |
    aiProcess_OptimizeMeshes |
    aiProcess_SplitLargeMeshes
);

namespace glsb {

bool Mesh::loadMesh(const char *pFilename) {
    mTextures.clear();
    bool res = false;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pFilename, ASSIMP_LOAD_FLAGS);

    if(scene) {
        res = initFromScene(scene, pFilename);
    }
    else {
        std::cout << "ERROR::ASSIMP::FILE::" << pFilename << std::endl;
    }

    return res;
}

void Mesh::render() {
    uint32_t VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for(auto& entry : mEntries) {
        glBindBuffer(GL_ARRAY_BUFFER, entry.VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entry.EBO);

        const uint32_t materialIndex = entry.materialIndex;

        if (materialIndex < mTextures.size() && mTextures[materialIndex]) {
            mTextures[materialIndex]->bind();
        }

        glDrawElements(GL_TRIANGLES, (int)entry.numIndices, GL_UNSIGNED_INT, nullptr);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindVertexArray(0);
}

bool Mesh::initFromScene(const aiScene *pScene, const char *pFilename) {
    mEntries.resize(pScene->mNumMeshes);
    mTextures.resize(pScene->mNumMaterials);

    for(size_t i = 0; i < mEntries.size(); ++i) {
        const aiMesh* mesh = pScene->mMeshes[i];
        initMesh(i, mesh);
    }

    return initMaterials(pScene, pFilename);
}

void Mesh::initMesh(uint32_t pIndex, const aiMesh *paiMesh) {
    mEntries[pIndex].materialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for(size_t i = 0; i < paiMesh->mNumVertices; ++i) {
        const aiVector3D* pos = &(paiMesh->mVertices[i]);
        const aiVector3D* normal = &(paiMesh->mNormals[i]);
        const aiVector3D* texCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        auto ai_to_glm3 = [](const aiVector3D* v) {
            return glm::vec3(v->x, v->y, v->z);
        };
        auto ai_to_glm2 = [](const aiVector3D* v) {
            return glm::vec2(v->x, v->y);
        };

        Vertex vertex(ai_to_glm3(pos), ai_to_glm2(texCoord), ai_to_glm3(normal));
        vertices.push_back(vertex);
    }

    for (size_t i = 0; i < paiMesh->mNumFaces; ++i) {
        const aiFace& face = paiMesh->mFaces[i];
        assert(face.mNumIndices == 3);
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    mEntries[pIndex].init(vertices, indices);
}

bool Mesh::initMaterials(const aiScene *pScene, const char *pFilename) {
    std::string filename = pFilename;

    std::string::size_type slashIndex = filename.find_last_of('/');
    std::string dir;

    if (slashIndex == std::string::npos) {
        dir = '.';
    }
    else if (slashIndex == 0) {
        dir = '/';
    }
    else {
        dir = filename.substr(0, slashIndex);
    }

    bool res = true;

    // Initialize the materials
    for (size_t i = 0; i < pScene->mNumMaterials; ++i) {
        const aiMaterial* material = pScene->mMaterials[i];

        mTextures[i] = nullptr;

        if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString path;

            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) {
                std::string fullPath = dir + "/" + path.data;
                std::replace(fullPath.begin(), fullPath.end(), '\\', '/');

                std::string extension = fullPath.substr(fullPath.find_last_of('.') + 1);
                int channels = GL_RGB;
                if(extension == "png") {
                    channels = GL_RGBA;
                }

#ifndef NDEBUG
                std::cout << fullPath << '\n';
#endif

                mTextures[i] = Texture::newTexture();
                mTextures[i]->addTexture2D(fullPath.c_str(), "texture_diffuse1", channels);
            }
        }
    }

    return res;
}

} // glsb