#include "camera.hpp"

#include <cmath>

namespace glsb {

void Camera::translateForward(float pSpeed) {
    //mPos += pSpeed * glm::vec3(mFront.x, 0.0f, mFront.z);
    mPos += pSpeed * glm::vec3(mFront.x, mFront.y, mFront.z);
}

void Camera::translateBackward(float pSpeed) {
    //mPos -= pSpeed * glm::vec3(mFront.x, 0.0f, mFront.z);
    mPos -= pSpeed * glm::vec3(mFront.x, mFront.y, mFront.z);
}

void Camera::translateLeft(float pSpeed) {
    mPos -= glm::normalize(glm::cross(mFront, mUp) * pSpeed) * 0.05f;
}

void Camera::translateRight(float pSpeed) {
    mPos += glm::normalize(glm::cross(mFront, mUp) * pSpeed) * 0.05f;
}

void Camera::lookAround(float pX, float pY) {
    static bool firstClick = true;
    if(firstClick) {
        mX = pX;
        mY = pY;
        firstClick = false;
    }

    float xOffset = pX - mX;
    float yOffset = mY - pY;
    mX = pX;
    mY = pY;

    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    mYaw += xOffset;
    mPitch += yOffset;

    if(mPitch > 89.0f)
        mPitch = 89.0f;
    if(mPitch < -89.0f)
        mPitch = -89.0f;

    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)));
    front.y = static_cast<float>(sin(glm::radians(mPitch)));
    front.z = static_cast<float>(sin(glm::radians(mYaw) * cos(glm::radians(mPitch))));

    mFront = glm::normalize(front);
}

void Camera::apply(GLFWwindow *pWindow, Shader* pShader) {
    int width, height;
    glfwGetFramebufferSize(pWindow, &width, &height);
    float aspect = (float)width / (float)height;

    pShader->use();
    glm::mat4 projection = glm::perspective(glm::radians(mFov), aspect, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(mPos, mPos + mFront, mUp);

    pShader->setUniform("view", view);
    pShader->setUniform("projection", projection);
}

} // glsb