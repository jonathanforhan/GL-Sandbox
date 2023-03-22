#ifndef GLSANDBOX_CUBE_HPP
#define GLSANDBOX_CUBE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "object.hpp"

namespace glsb {

class Cube : IObject {
public:
    Cube(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
    ~Cube();

    void scale(float x, float y, float z) override;
    void rotate(float x, float y, float z, float angle) override;
    void translate(float x, float y, float z) override;

    void render() override;
    void useTexture() override {}
};

} // glsb

#endif //GLSANDBOX_CUBE_HPP
