//
//  Window.cpp
//  Snake
//
//  Created by Глеб Косачёв on 06/03/2025.
//

#include "Window.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <iostream>
#include <queue>

void FramebufferSizeCallback(GLFWwindow *window, int32_t width, int32_t height)
{
    glViewport(0, 0, width, height);
}

static std::queue<std::pair<int32_t, int32_t>> Directions;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS) return;
    switch (key) {
        case GLFW_KEY_W:
        case GLFW_KEY_UP:
            Directions.emplace(0, 1);
            break;
        case GLFW_KEY_S:
        case GLFW_KEY_DOWN:
            Directions.emplace(0, -1);
            break;
        case GLFW_KEY_A:
        case GLFW_KEY_LEFT:
            Directions.emplace(-1, 0);
            break;
        case GLFW_KEY_D:
        case GLFW_KEY_RIGHT:
            Directions.emplace(1, 0);
            break;
    }
}

Window::Window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = static_cast<void *>(glfwCreateWindow(800, 800, "Snake", nullptr, nullptr));
    if (window == nullptr)
        throw std::runtime_error("Failed to create a window");
    glfwMakeContextCurrent(static_cast<GLFWwindow *>(window));
    gladLoadGL(glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(window), FramebufferSizeCallback);
    glfwSetWindowAspectRatio(static_cast<GLFWwindow *>(window), 1, 1);
    int32_t width, height;
    glfwGetFramebufferSize(static_cast<GLFWwindow *>(window), &width, &height);
    glViewport(0, 0, width, height);
    glfwSetKeyCallback(static_cast<GLFWwindow *>(window), KeyCallback);
}

Window::~Window()
{
    glfwDestroyWindow(static_cast<GLFWwindow *>(window));
    glfwTerminate();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(static_cast<GLFWwindow *>(window));
}

void Window::HandleEvents()
{
    glfwPollEvents();
}

void Window::UpdateImage()
{
    glfwSwapBuffers(static_cast<GLFWwindow *>(window));
}

std::pair<int32_t, int32_t> Window::GetUserInput()
{
    if (Directions.empty()) return std::make_pair(0, 0);
    std::pair<int32_t, int32_t> Result = Directions.front();
    Directions.pop();
    return Result;
}
