#include "plane.hpp"

#include <utility>

namespace glsb {

Plane::Plane(std::shared_ptr<Shader> pShader, std::shared_ptr<Texture> pTexture)
    : IObject(std::move(pShader), std::move(pTexture)) {
    GLfloat vertices[] = {
            // positions        // texture coords
             0.5f,  0.0f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.0f,  0.5f, 1.0f, 0.0f,
            -0.5f,  0.0f, -0.5f, 0.0f, 0.0f,
             0.5f,  0.0f, -0.5f, 0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    this->mVAO = VAO;
    this->mVBO = VBO;
    this->mEBO = EBO;
}

Plane::~Plane() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

void Plane::scale(float x, float y, float z) {
    IObject::scale(x, y, z);
}

void Plane::rotate(float x, float y, float z, float pAngle) {
    IObject::rotate(x, y, z, pAngle);
}

void Plane::translate(float x, float y, float z) {
    IObject::translate(x, y, z);
}

void Plane::render() {
    mShader->use();
    mShader->setUniform("model", mTransform);
    mShader->setUniform("texCoordScale", mTexCoordScale);

    mTexture->bind(*mShader);

    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

} // glsb