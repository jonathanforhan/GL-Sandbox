#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace glsb {

void Shader::add(const char* pPath, GLuint pType) {
    std::string pShaderCode;

    std::ifstream f;
    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string pShaderName = getShaderName(pType);

    std::stringstream ss;

    try {
        f.open(pPath);
        ss << f.rdbuf();
        f.close();
        pShaderCode = ss.str();
    } catch(std::ifstream::failure& e) {
        std::cout << "ERROR::" << pShaderName << "::SHADER::FILE_READ_FAILURE\n" <<  e.what() << std::endl;
    }

    const char* pShaderCodeCStr = pShaderCode.c_str();
    GLuint pShader = glCreateShader(pType);
    glShaderSource(pShader, 1, &pShaderCodeCStr, nullptr);
    glCompileShader(pShader);
    checkCompileErrors(pShader, pShaderName);

    mShaders.push_back(pShader);

}

void Shader::createProgram() {
    this->mID = glCreateProgram();

    for(const auto& pShader : mShaders) {
        glAttachShader(mID, pShader);
    }

    glLinkProgram(mID);
    checkCompileErrors(mID, "PROGRAM");

    for(const auto& pShader : mShaders) {
        glDeleteShader(pShader);
    }

    mShaders.clear();
}

void Shader::use() const {
    glUseProgram(mID);
}

// Name
void Shader::setUniform(const std::string &pName, bool pValue) const {
    glUniform1i(glGetUniformLocation(mID, pName.c_str()), (int)pValue);
}

void Shader::setUniform(const std::string &pName, int pValue) const {
    glUniform1i(glGetUniformLocation(mID, pName.c_str()), pValue);
}

void Shader::setUniform(const std::string &pName, float pValue) const {
    glUniform1f(glGetUniformLocation(mID, pName.c_str()), pValue);
}

void  Shader::setUniform(const std::string &pName, const glm::vec2 &pValue) const {
    glUniform2fv(glGetUniformLocation(mID, pName.c_str()), 1, &pValue[0]);
}

void  Shader::setUniform(const std::string &pName, float x, float y) const {
    glUniform2f(glGetUniformLocation(mID, pName.c_str()), x, y);
}

void  Shader::setUniform(const std::string &pName, const glm::vec3 &pValue) const {
    glUniform3fv(glGetUniformLocation(mID, pName.c_str()), 1, &pValue[0]);
}

void  Shader::setUniform(const std::string &pName, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(mID, pName.c_str()), x, y, z);
}

void  Shader::setUniform(const std::string &pName, const glm::vec4 &pValue) const {
    glUniform4fv(glGetUniformLocation(mID, pName.c_str()), 1, &pValue[0]);
}

void  Shader::setUniform(const std::string &pName, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(mID, pName.c_str()), x, y, z, w);
}

void  Shader::setUniform(const std::string &pName, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(mID, pName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void  Shader::setUniform(const std::string &pName, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(mID, pName.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void  Shader::setUniform(const std::string &pName, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(mID, pName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ID
void Shader::setUniform(const GLuint pID, bool pValue) const {
    glUniform1i(pID, (int)pValue);
}

void Shader::setUniform(const GLuint pID, int pValue) const {
    glUniform1i(pID, pValue);
}

void Shader::setUniform(const GLuint pID, float pValue) const {
    glUniform1f(pID, pValue);
}

void  Shader::setUniform(const GLuint pID, const glm::vec2 &pValue) const {
    glUniform2fv(pID, 1, &pValue[0]);
}

void  Shader::setUniform(const GLuint pID, float x, float y) const {
    glUniform2f(pID, x, y);
}

void  Shader::setUniform(const GLuint pID, const glm::vec3 &pValue) const {
    glUniform3fv(pID, 1, &pValue[0]);
}

void  Shader::setUniform(const GLuint pID, float x, float y, float z) const {
    glUniform3f(pID, x, y, z);
}

void  Shader::setUniform(const GLuint pID, const glm::vec4 &pValue) const {
    glUniform4fv(pID, 1, &pValue[0]);
}

void  Shader::setUniform(const GLuint pID, float x, float y, float z, float w) const {
    glUniform4f(pID, x, y, z, w);
}

void  Shader::setUniform(const GLuint pID, const glm::mat2 &mat) const {
    glUniformMatrix2fv(pID, 1, GL_FALSE, &mat[0][0]);
}

void  Shader::setUniform(const GLuint pID, const glm::mat3 &mat) const {
    glUniformMatrix3fv(pID, 1, GL_FALSE, &mat[0][0]);
}

void  Shader::setUniform(const GLuint pID, const glm::mat4 &mat) const {
    glUniformMatrix4fv(pID, 1, GL_FALSE, &mat[0][0]);
}

GLuint Shader::getUniformLocation(const char* pName) {
    return glGetUniformLocation(this->mID, pName);
}

GLint Shader::getID() {
    return (int)mID;
}

/* Private */
void Shader::checkCompileErrors(GLuint pShader, const std::string& pType) {
    int success;
    char infoLog[1024];
    if(pType != "PROGRAM") {
        glGetShaderiv(pShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(pShader, 1024, nullptr, infoLog);
            std::cout << "ERROR::" << pType << "::SHADER_COMPILATION_FAILURE\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(pShader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(pShader, 1024, nullptr, infoLog);
            std::cout << "ERROR::" << pType << "::PROGRAM_LINKING_FAILURE\n" << infoLog << std::endl;
        }
    }
}

std::string Shader::getShaderName(GLuint pType) {
    switch(pType) {
        case GL_VERTEX_SHADER:
            return "VERTEX";
        case GL_FRAGMENT_SHADER:
            return "FRAGMENT";
        case GL_TESS_CONTROL_SHADER:
            return "TESS_CONTROL";
        case GL_TESS_EVALUATION_SHADER:
            return "TESS_EVALUATION";
        case GL_GEOMETRY_SHADER:
            return "GEOMETRY_SHADER";
        default:
            throw std::runtime_error("ERROR::BAD_SHADER_TYPE\n");
    }
}

} // glsb