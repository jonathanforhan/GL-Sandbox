#include "application.hpp"

#include<iostream>

#include "shader/shader.hpp"
#include "plane.hpp"
#include "cube.hpp"

namespace glsb {

WindowState windowState;

void windowStateCallback(GLFWwindow*, int pWidth, int pHeight) {
    windowState.setWindowState(pWidth, pHeight);
    glViewport(0, 0, pWidth, pHeight);
}

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
};

Application::~Application() {
    glfwTerminate();
}

int Application::run() {
    GLFWwindow* window = glfwCreateWindow(800, 800, "glsandbox", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowStateCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

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
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        glClearColor( 0.3f, 0.1f, 0.4f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float aspect = (float)windowState.getWidth() / (float)windowState.getHeight();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -3.0f));

        shader->use();
        shader->setUniform("view", view);
        shader->setUniform("projection", projection);

        plane.render();

        cube_spin.rotate(1.0f, 1.0f, 0, 1.0f);
        cube_still.render();
        cube_spin.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

} // glsb