#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window
{
public:
    static Window* Instance() {
        if (!s_Instance)
            return nullptr;
        return s_Instance;
    }
public:
    Window();
    ~Window();

    void Update();

    bool ShouldClose();
    GLFWwindow* GetNativeWindow();
private:
    static Window* s_Instance;
private:
    GLFWwindow* m_Window;
};