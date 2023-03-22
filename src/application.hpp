#ifndef GLSANDBOX_APPLICATION_HPP
#define GLSANDBOX_APPLICATION_HPP

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.hpp"

namespace glsb {

class Application {
public:
    Application();
    ~Application();

    int run();
};

} // glsb

#endif //GLSANDBOX_APPLICATION_HPP
