#include "ParticleSystem.hpp"

#include <random>

ParticleSystem::ParticleSystem(const uint maxParticles, float spawnRadius)
    : m_MaxParticles(maxParticles), m_SpawnRadius(spawnRadius)
{
    m_Particles = new Particle[m_MaxParticles];

    m_MinLifeSpan = 0.5f;
    m_MaxLifeSpan = 7.0f;

    m_MinVel = 0.1f;
    m_MaxVel = 0.2f;

    m_MinSize = 0.001f;
    m_MaxSize = 0.005f;

    m_StartCol = Float4(0.55, 0.02, 0.02f, 1.0f);
    m_EndCol = Float4(1.0, 0.78, 0.13f, 1.0f);
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
            float size = glm::linearRand<float>(m_MinSize, m_MaxSize);
            float velMag = glm::linearRand<float>(m_MinVel, m_MaxVel);
            float accMag = glm::linearRand<float>(0.05f, 0.1f);
            particle = Particle{
                0.0f,
                glm::linearRand<float>(m_MinLifeSpan, m_MaxLifeSpan),
                { m_Position.x + radius * glm::cos(theta), m_Position.y + radius * glm::sin(theta), 0.0f },
                glm::linearRand<float>(0.0f, 2.0f * glm::pi<float>()),
                { size, size },
                { velMag * glm::cos(theta), velMag * glm::sin(theta), 0.0f },
                glm::linearRand<float>(0.01f, 0.05f),
                { accMag * glm::cos(theta), accMag * glm::sin(theta), 0.0f },
                glm::linearRand<float>(0.01f, 0.5f),
                m_StartCol,
            };
        }
        else
        {
            // particle.Vel += particle.RAcc * delta;
            // particle.Vel += Float3{ 0.0, -0.98f, 0.0f } * delta;
            
            particle.RVel += particle.RAcc * delta;
            particle.Position += particle.Vel * delta;
            particle.Rotation += particle.RVel * delta;
            particle.Color = m_StartCol + ((m_EndCol - m_StartCol) * (particle.Age / particle.LifeSpan));
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
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(175.0f, 325.0f));
    ImGui::Begin("Particle Settings", 0, ImGuiWindowFlags_NoResize);

    // ImGui::SliderFloat2("Position", &m_Position[0], -1.0f, 1.0f);
    ImGui::PushID("Lifespan");
    ImGui::Text("Lifespan:");
    ImGui::SliderFloat("Min", &m_MinLifeSpan, 0.1, m_MaxLifeSpan);
    ImGui::SliderFloat("Max", &m_MaxLifeSpan, m_MinLifeSpan, 10.0f);
    ImGui::PopID();

    ImGui::PushID("Generation Radius");
    ImGui::Text("Generation Radius:");
    ImGui::SliderFloat("", &m_SpawnRadius, 0.01, 1.0f);
    ImGui::PopID();

    ImGui::PushID("Particle Velocity");
    ImGui::Text("Particle Velocity:");
    ImGui::SliderFloat("Min", &m_MinVel, 0.1, m_MaxVel);
    ImGui::SliderFloat("Max", &m_MaxVel, m_MinVel, 1.0f);
    ImGui::PopID();

    ImGui::PushID("Particle Size");
    ImGui::Text("Particle Size:");
    ImGui::SliderFloat("Min", &m_MinSize, 0.0001, m_MaxSize);
    ImGui::SliderFloat("Max", &m_MaxSize, m_MinSize, 0.1f);
    ImGui::PopID();

    ImGui::PushID("Color");
    ImGui::Text("Color:");
    ImGui::ColorEdit3("Start", &m_StartCol[0]);
    ImGui::ColorEdit3("End", &m_EndCol[0]);
    ImGui::PopID();

    ImGui::End();
}

void ParticleSystem::SetPos(Float2 pos)
{
    m_Position = pos;
}
