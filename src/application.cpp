#include "application.hpp"

#include<iostream>

#include "shader.hpp"
#include "plane.hpp"
#include "cube.hpp"
#include "model.hpp"

namespace glsb {

bool cursorChange = true;
float xCursorPos{}, yCursorPos{};

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(1920, 1080, "glsandbox", nullptr, nullptr);
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

    std::shared_ptr<Shader> lightShader = Shader::newShader();
    lightShader->add("../../shaders/lighting.vert", GL_VERTEX_SHADER);
    lightShader->add("../../shaders/lighting.frag", GL_FRAGMENT_SHADER);
    lightShader->createProgram();

    std::shared_ptr<Shader> modelShader = Shader::newShader();
    modelShader->add("../../shaders/model.vert", GL_VERTEX_SHADER);
    modelShader->add("../../shaders/model.frag", GL_FRAGMENT_SHADER);
    modelShader->createProgram();

    std::shared_ptr<Texture> stone = Texture::newTexture();
    stone->addTexture2D("../../textures/stone_brick.jpg", "tex", GL_RGB);

    std::shared_ptr<Texture> lamp = Texture::newTexture();
    lamp->addTexture2D("../../textures/lamp.jpg", "tex", GL_RGB);

    Plane plane(shader, stone);
    plane.scale(30, 0, 30);

    Cube lamps0 = Cube(lightShader, lamp);
    Cube lamps1 = Cube(lightShader, lamp);
    Cube lamps2 = Cube(lightShader, lamp);

    lamps0.translate(0, 0.5f, 0);
    lamps1.translate(0, 1.5f, 0);
    lamps2.translate(1.0f, 0.5f, 0);

    Model model("../../assets/backpack/backpack.obj");

    while(!glfwWindowShouldClose(window)) {
        calcDeltaT();
        handleInput(window);

        if(cursorChange) {
            camera.lookAround(xCursorPos, yCursorPos);
            cursorChange = false;
        }

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.apply(window, &*shader);
        camera.apply(window, &*lightShader);
        camera.apply(window, &*modelShader);

        glm::vec4 lightColor = glm::vec4(0.8f, 0.6f, 0.5f, 1.0f);

        shader->use();
        shader->setUniform("lightColor", lightColor);
        shader->setUniform("lightPos", glm::vec3(0.0f, 2.5f, 0.0f));
        shader->setUniform("camPos", camera.getPosition());

        plane.render();

        lightShader->use();
        lightShader->setUniform("lightColor", lightColor);
        lamps0.render();
        lamps1.render();
        lamps2.render();

        modelShader->use();
        glm::mat4 mod = glm::mat4(1.0f);
        mod = glm::translate(mod, glm::vec3(10.0f, 2.0f, 0.0f)); // translate it down so it's at the center of the scene
        mod = glm::scale(mod, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        modelShader->setUniform("model", mod);

        model.Draw((Shader&)*shader);

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