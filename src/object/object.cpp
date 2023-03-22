#include "object.hpp"

namespace glsb {

void IObject::scale(float x, float y, float z) {
    glm::mat4 scale = glm::scale(mScale, glm::vec3(x, y, z));
    mTransform *= scale;
    mTexCoordScale = glm::vec2(x, z);
}

void IObject::rotate(float x, float y, float z, float pAngle) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(pAngle), glm::vec3(x, y, z));
    mTransform *= rotation;
}

void IObject::translate(float x, float y, float z) {
    glm::mat4 translation = glm::translate(mTranslation, glm::vec3(x, y, z));
    mTransform *= translation;
}

} // glsb
