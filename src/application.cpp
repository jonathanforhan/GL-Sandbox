#include "application.hpp"

#include<iostream>

#include "shader.hpp"
#include "plane.hpp"
#include "cube.hpp"
#include "mesh.hpp"

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

struct {
    float rotation = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
} test;

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

    Mesh hall;
    hall.loadMesh("../../assets/hall/NHMHintzeHall01.obj");

    glm::mat4 hall_transform = glm::mat4(1.0f);
    hall_transform = glm::rotate(hall_transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

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

        lightShader->use();
        lightShader->setUniform("lightColor", lightColor);

        modelShader->use();

        modelShader->setUniform("model", hall_transform);
        hall.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void Application::windowResizeCallback(GLFWwindow*, int pWidth, int pHeight) {
    glViewport(0, 0, pWidth, pHeight);
}

void Application::mouseCallback(GLFWwindow*, double xPos, double yPos) {
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

    float cameraSpeed = static_cast<float>(6 * deltaT);

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
    glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        cameraSpeed *= 2;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.translateForward(cameraSpeed);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.translateBackward(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.translateLeft(cameraSpeed);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.translateRight(cameraSpeed);

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        test.rotation -= 1.0f;
        std::cout << test.rotation << '\n';
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        test.rotation += 1.0f;
        std::cout << test.rotation << '\n';
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        test.y += 1.0f;
        std::cout << "test.y: " << test.y << '\n';
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        test.y -= 1.0f;
        std::cout << "test.y: " << test.y << '\n';
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        test.x += 1.0f;
        std::cout << "test.x: " << test.x << '\n';
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        test.x -= 1.0f;
        std::cout << "test.x: " << test.x << '\n';
    }
}

} // glsb