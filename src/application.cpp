#include "application.hpp"

#include<iostream>

#include "shader.hpp"
#include "plane.hpp"
#include "cube.hpp"

namespace glsb {

bool cursorChange = true;
float xCursorPos{}, yCursorPos{};

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(1920, 1080, "glsandbox", nullptr, nullptr);
    // debug
    //this->window = glfwCreateWindow(800, 800, "glsandbox", nullptr, nullptr);
    if(!window) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }
    glEnable(GL_DEPTH_TEST);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    xCursorPos = (float)width/2;
    yCursorPos = (float)height/2;
};

Application::~Application() {
    glfwTerminate();
}

int Application::run() {
    std::shared_ptr<Shader> shader = Shader::newShader();
    shader->add("../../shaders/basic.vert", GL_VERTEX_SHADER);
    shader->add("../../shaders/basic.frag", GL_FRAGMENT_SHADER);
    shader->createProgram();

    std::shared_ptr<Texture> ruby = Texture::newTexture();
    ruby->addTexture2D("../../textures/ruby.jpg", "tex", GL_RGB);
    Cube cube_still(shader, ruby);
    Cube cube_spin(shader, ruby);

    std::shared_ptr<Texture> tile = Texture::newTexture();
    tile->addTexture2D("../../textures/tile.jpg", "tex", GL_RGB);
    Plane plane(shader, tile);

    plane.scale(30, 0, 30);
    cube_still.scale(0.5f, 0.5f, 0.5f);
    cube_spin.scale(0.5f, 0.5f, 0.5f);

    cube_spin.translate(0, 2.5f, 0);
    cube_still.translate(0, 0.5f, 0);

    while(!glfwWindowShouldClose(window)) {
        calcDeltaT();
        handleInput(window);

        if(cursorChange) {
            camera.lookAround(xCursorPos, yCursorPos);
            cursorChange = false;
        }

        glClearColor( 0.3f, 0.1f, 0.4f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.apply(window, &*shader);

        plane.render();

        cube_spin.rotate(1.0f, 1.0f, 0, 1.0f);
        cube_still.render();
        cube_spin.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void Application::windowResizeCallback(GLFWwindow*, int pWidth, int pHeight) {
    glViewport(0, 0, pWidth, pHeight);
}

void Application::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
    xCursorPos = static_cast<float>(xPos);
    yCursorPos = static_cast<float>(yPos);
    cursorChange = true;
}

void Application::calcDeltaT() {
    float currFrame = static_cast<float>(glfwGetTime());
    deltaT = currFrame - lastFrame;
    lastFrame = currFrame;
}

void Application::handleInput(GLFWwindow*) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(5 * deltaT);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.translateForward(cameraSpeed);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.translateBackward(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.translateLeft(cameraSpeed);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.translateRight(cameraSpeed);
}

} // glsb