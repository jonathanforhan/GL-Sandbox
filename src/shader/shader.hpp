#ifndef GLSANDBOX_SHADER_HPP
#define GLSANDBOX_SHADER_HPP

#include <glad/glad.h>
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
    void add(const char* pPath, GLuint pType);
    void createProgram();
    void use() const;

    // setters
    void setUniform(const std::string &pName, bool pValue) const;
    void setUniform(const std::string &pName, int pValue) const;
    void setUniform(const std::string &pName, float pValue) const;
    void setUniform(const std::string &pName, const glm::vec2 &pValue) const;
    void setUniform(const std::string &pName, float x, float y) const;
    void setUniform(const std::string &pName, const glm::vec3 &pValue) const;
    void setUniform(const std::string &pName, float x, float y, float z) const;
    void setUniform(const std::string &pName, const glm::vec4 &pValue) const;
    void setUniform(const std::string &pName, float x, float y, float z, float w) const;
    void setUniform(const std::string &pName, const glm::mat2 &mat) const;
    void setUniform(const std::string &pName, const glm::mat3 &mat) const;
    void setUniform(const std::string &pName, const glm::mat4 &mat) const;
    void setUniform(GLuint pID, bool pValue) const;
    void setUniform(GLuint pID, int pValue) const;
    void setUniform(GLuint pID, float pValue) const;
    void setUniform(GLuint pID, const glm::vec2 &pValue) const;
    void setUniform(GLuint pID, float x, float y) const;
    void setUniform(GLuint pID, const glm::vec3 &pValue) const;
    void setUniform(GLuint pID, float x, float y, float z) const;
    void setUniform(GLuint pID, const glm::vec4 &pValue) const;
    void setUniform(GLuint pID, float x, float y, float z, float w) const;
    void setUniform(GLuint pID, const glm::mat2 &mat) const;
    void setUniform(GLuint pID, const glm::mat3 &mat) const;
    void setUniform(GLuint pID, const glm::mat4 &mat) const;

    // getters
    GLuint getUniformLocation(const char* pName);

    GLint getID();

private:
    uint32_t mID{};
    static void checkCompileErrors(uint32_t pShader, const std::string& pType);
    static std::string getShaderName(GLuint pType);

    std::vector<GLuint> mShaders{};
};

} // glsb

#endif //GLSANDBOX_SHADER_HPP
