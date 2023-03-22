#ifndef GLSANDBOX_SHADER_HPP
#define GLSANDBOX_SHADER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace glsb {

class Shader {
public:
    Shader() = default;
    ~Shader() { glDeleteProgram(this->mID); }

    static std::shared_ptr<Shader> newShader() { return std::make_shared<Shader>(); };
    void add(const char* path, GLuint type);
    void createProgram();
    void use() const;

    // setters
    void setUniform(const std::string &name, bool value) const;
    void setUniform(const std::string &name, int value) const;
    void setUniform(const std::string &name, float value) const;
    void setUniform(const std::string &name, const glm::vec2 &value) const;
    void setUniform(const std::string &name, float x, float y) const;
    void setUniform(const std::string &name, const glm::vec3 &value) const;
    void setUniform(const std::string &name, float x, float y, float z) const;
    void setUniform(const std::string &name, const glm::vec4 &value) const;
    void setUniform(const std::string &name, float x, float y, float z, float w) const;
    void setUniform(const std::string &name, const glm::mat2 &mat) const;
    void setUniform(const std::string &name, const glm::mat3 &mat) const;
    void setUniform(const std::string &name, const glm::mat4 &mat) const;
    void setUniform(GLuint ID, bool value) const;
    void setUniform(GLuint ID, int value) const;
    void setUniform(GLuint ID, float value) const;
    void setUniform(GLuint ID, const glm::vec2 &value) const;
    void setUniform(GLuint ID, float x, float y) const;
    void setUniform(GLuint ID, const glm::vec3 &value) const;
    void setUniform(GLuint ID, float x, float y, float z) const;
    void setUniform(GLuint ID, const glm::vec4 &value) const;
    void setUniform(GLuint ID, float x, float y, float z, float w) const;
    void setUniform(GLuint ID, const glm::mat2 &mat) const;
    void setUniform(GLuint ID, const glm::mat3 &mat) const;
    void setUniform(GLuint ID, const glm::mat4 &mat) const;

    // getters
    GLuint getUniformLocation(const char* name);

    GLint getID();

private:
    uint32_t mID{};
    static void checkCompileErrors(uint32_t shader, const std::string& type);
    static std::string getShaderName(GLuint type);

    std::vector<GLuint> mShaders{};
};

} // glsb

#endif //GLSANDBOX_SHADER_HPP
