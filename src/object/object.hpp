#ifndef GLSANDBOX_OBJECT_HPP
#define GLSANDBOX_OBJECT_HPP

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"

namespace glsb {

class IObject {
public:
    explicit IObject(std::shared_ptr<Shader> pShader, std::shared_ptr<Texture> pTexture)
        : mShader(std::move(pShader)), mTexture(std::move(pTexture)) {};

    virtual void useShader() { mShader->use(); };
    virtual void useTexture() = 0;
    virtual void render() = 0;

    virtual void scale(float x, float y, float z);
    virtual void rotate(float x, float y, float z, float pAngle);
    virtual void translate(float x, float y, float z);

protected:
    std::shared_ptr<Shader> mShader{ nullptr };
    std::shared_ptr<Texture> mTexture{ nullptr };

    uint32_t mVAO{}, mVBO{}, mEBO{};

    glm::mat4 mScale = glm::mat4(1.0f);
    glm::mat4 mRotation = glm::mat4(1.0f);
    glm::mat4 mTranslation = glm::mat4(1.0f);
    glm::mat4 mTransform = glm::mat4(1.0f);

    glm::vec2 mTexCoordScale = glm::vec2(1.0f, 1.0f);
};

} // glsb

#endif //GLSANDBOX_OBJECT_HPP
