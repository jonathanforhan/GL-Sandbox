#include "cube.hpp"

#include <utility>

namespace glsb {

Cube::Cube(std::shared_ptr<Shader> pShader, std::shared_ptr<Texture> pTexture)
        : IObject(std::move(pShader), std::move(pTexture)) {
    GLfloat vertices[] = {
         // positions           // tex         // normals
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f,    1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,    0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,    0.0f,  1.0f,  0.0f,

         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,    0.0f, -1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,    0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 1.0f,    0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f,    0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,    0.0f,  0.0f,  1.0f,

         0.5f,  0.5f, -0.5f,    1.0f, 0.0f,    0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f,    0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    0.0f,  0.0f, -1.0f,
    };

    GLuint indices[] = {
        0,  1,  3,  3,  1,  2,
        4,  5,  7,  7,  5,  6,
        8,  9,  11, 11, 9,  10,
        12, 13, 15, 15, 13, 14,
        16, 17, 19, 19, 17, 18,
        20, 21, 23, 23, 21, 22,
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    this->mVAO = VAO;
    this->mVBO = VBO;
    this->mEBO = EBO;
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

void Cube::scale(float x, float y, float z) {
    IObject::scale(x, y, z);
}

void Cube::rotate(float x, float y, float z, float pAngle) {
    IObject::rotate(x, y, z, pAngle);
}

void Cube::translate(float x, float y, float z) {
    IObject::translate(x, y, z);
}

void Cube::render() {
    mShader->use();
    mShader->setUniform("model", mTransform);
    mShader->setUniform("texCoordScale", mTexCoordScale);

    if(mTexture)
        mTexture->bind(*mShader);

    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

} // glsb
