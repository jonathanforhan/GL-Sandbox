#ifndef GLSANDBOX_TEXTURE_HPP
#define GLSANDBOX_TEXTURE_HPP

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <string>
#include "shader.hpp"

namespace glsb {

class Texture {
public:
    Texture() = default;
    ~Texture() {
        glDeleteTextures(1, &mID);
    }

    static std::shared_ptr<Texture> newTexture() { return std::make_shared<Texture>(); }
    void addTexture2D(const char* pPath, const char* pName, GLint pChannels);

    void bind(const Shader& pShader);

private:
    std::string mName{};
    GLuint mID{};
};

} // glsb

#endif //GLSANDBOX_TEXTURE_HPP
