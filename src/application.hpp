#ifndef GLSANDBOX_APPLICATION_HPP
#define GLSANDBOX_APPLICATION_HPP

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera/camera.hpp"

namespace glsb {

class Application {
public:
    Application();
    ~Application();

    int run();
private:
    GLFWwindow* window = nullptr;

    Camera camera{};

    // callbacks
    static void windowResizeCallback(GLFWwindow*, int pWidth, int pHeight);
    static void mouseCallback(GLFWwindow *window, double xPos, double yPos);

    // timings
    float lastFrame{}, deltaT{};
    void calcDeltaT();

    // user input
    void handleInput(GLFWwindow*);
};

} // glsb

#endif //GLSANDBOX_APPLICATION_HPP
