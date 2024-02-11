#include <iostream>

#include "window/Window.hpp"
#include "renderer/Renderer.hpp"

int main() {
    std::cout << "Hello World!" << std::endl;

    Window window;
    Renderer renderer;
    renderer.SetClearColor({ 0.1f, 0.2f, 0.3f, 1.0f });

    while (!window.ShouldClose())
    {
        renderer.Clear();
        renderer.DrawQuad({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        renderer.Render();
        window.Update();
    }

    return 0;
}