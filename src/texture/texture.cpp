#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

namespace glsb {

void Texture::addTexture2D(const char* pPath, const char* pName, int pChannels) {
    uint32_t tex;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(pPath, &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, pChannels, width, height, 0, pChannels, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "ERROR::STBI_LOAD_FAILURE\n";
    }
    stbi_image_free(data);

    this->mName = pName;
    this->mID = tex;
}

void Texture::bind(const Shader &pShader) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mID);
    pShader.setUniform(mName, 0);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mID);
}

} // glsb