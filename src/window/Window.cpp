#include "Window.hpp"

#include <iostream>

Window* Window::s_Instance = nullptr;

Window::Window()
{
    if (!s_Instance)
        s_Instance = this;

    if (!glfwInit())
        std::cout << "GLFW Error!" << std::endl;
    m_Window = glfwCreateWindow(800, 600, "Particle Demo", NULL, NULL);
    if (!m_Window)
        std::cout << "GLFW Error!" << std::endl;
    glfwMakeContextCurrent(m_Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_Window);
}

GLFWwindow* Window::GetNativeWindow()
{
    return m_Window;
}