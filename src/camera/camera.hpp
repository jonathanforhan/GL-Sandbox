#ifndef GLSANDBOX_CAMERA_HPP
#define GLSANDBOX_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader/shader.hpp"

namespace glsb {

class Camera {
public:
    Camera() = default;

    void translateForward(float speed);
    void translateBackward(float speed);
    void translateLeft(float speed);
    void translateRight(float speed);

    void lookAround(float x, float y);

    void apply(GLFWwindow *window, Shader *shader);

private:
    glm::vec3 mPos = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 mFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float mX{}, mY{};

    float mYaw = 90.0f;
    float mPitch = 0.0f;
    float mFov = 45.0f;
};

} // glsb

#endif //GLSANDBOX_CAMERA_HPP
