#ifndef GLSANDBOX_TEXTURE_HPP
#define GLSANDBOX_TEXTURE_HPP

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
    void addTexture2D(const char* path, const char* name, int channels);

    void bind(const Shader& shader);
    void bind();

private:
    std::string mName{};
    uint32_t mID{};

};

} // glsb

#endif //GLSANDBOX_TEXTURE_HPP
