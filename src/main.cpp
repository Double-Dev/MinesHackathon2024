#include <iostream>
#include <random>

#include "window/Window.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/ParticleSystem.hpp"

int main() {
    uint numParticles;
    std::cout << "Enter the Number of Particles to Simulate: ";
    std::cin >> numParticles;

    Window window;
    Renderer renderer;
    renderer.SetClearColor({ 0.1f, 0.2f, 0.3f, 1.0f });

    ParticleSystem pSys(numParticles, 0.1f);

    double lastTime = glfwGetTime();
    float timer = 0.0f;
    uint frames = 0;
    while (!window.ShouldClose())
    {
        double currentTime = glfwGetTime();
        float delta = (float)(currentTime - lastTime);
        lastTime = currentTime;
        timer += delta;
        if (timer >= 1.0f)
        {
            std::cout << "FPS: " << frames << std::endl;
            timer = 0.0f;
            frames = 0;
        }

        double x, y;
        glfwGetCursorPos(window.GetNativeWindow(), &x, &y);
        int width, height;
        glfwGetWindowSize(window.GetNativeWindow(), &width, &height);

        pSys.SetPos({((float)(x / width)) * 2.0f - 1.0f, -(((float)(y / height)) * 2.0f - 1.0f)});

        renderer.Clear();

        pSys.Update(delta);
        pSys.Render(&renderer);
        
        renderer.Render();
        renderer.BeginImGuiRender();
        pSys.ImGuiRender();
        renderer.EndImGuiRender();
        window.Update();
        frames++;
    }

    return 0;
}