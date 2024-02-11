#include "ParticleSystem.hpp"

#include <random>

ParticleSystem::ParticleSystem(const uint maxParticles, float spawnRadius)
    : m_MaxParticles(maxParticles), m_SpawnRadius(spawnRadius)
{
    m_Particles = new Particle[m_MaxParticles];
}

ParticleSystem::~ParticleSystem()
{
    delete[] m_Particles;
}


void ParticleSystem::Update(float delta)
{
    for (int i = 0; i < m_MaxParticles; i++)
    {
        Particle& particle = m_Particles[i];
        particle.Age += delta;
        if (particle.Age > particle.LifeSpan)
        {
            float theta = glm::linearRand<float>(0.0f, 2.0f * glm::pi<float>());
            float radius = glm::linearRand<float>(0.0f, m_SpawnRadius);
            float size = glm::linearRand<float>(0.001f, 0.005);
            float velMag = glm::linearRand<float>(0.1f, 0.2f);
            float accMag = glm::linearRand<float>(0.05f, 0.1f);
            particle = Particle{
                0.0f,
                glm::linearRand<float>(0.5f, 7.0f),
                { m_Position.x + radius * glm::cos(theta), m_Position.y + radius * glm::sin(theta), 0.0f },
                glm::linearRand<float>(0.0f, 2.0f * glm::pi<float>()),
                { size, size },
                { velMag * glm::cos(theta), velMag * glm::sin(theta), 0.0f },
                glm::linearRand<float>(0.01f, 0.05f),
                { accMag * glm::cos(theta), accMag * glm::sin(theta), 0.0f },
                glm::linearRand<float>(0.01f, 0.5f),
                { glm::linearRand<float>(0.0f, 1.0f), glm::linearRand<float>(0.0f, 1.0f), glm::linearRand<float>(0.0f, 1.0f), 1.0f },
            };
        }
        else
        {
            // particle.Vel += particle.RAcc * delta;
            particle.Vel += Float3{ 0.0, -0.98f, 0.0f } * delta;
            particle.RVel += particle.RAcc * delta;
            particle.Position += particle.Vel * delta;
            particle.Rotation += particle.RVel * delta;
        }
    }
}

void ParticleSystem::Render(Renderer* renderer)
{
    for (int i = 0; i < m_MaxParticles; i++)
    {
        Particle particle = m_Particles[i];
        renderer->DrawQuad(particle.Position, particle.Rotation, particle.Size, particle.Color);
    }
}

void ParticleSystem::ImGuiRender()
{
    ImGui::ShowDemoWindow();

    ImGui::Begin("Settings");

    

    ImGui::End();
}

void ParticleSystem::SetPos(Float2 pos)
{
    m_Position = pos;
}
