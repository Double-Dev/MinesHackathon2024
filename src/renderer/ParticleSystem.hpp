#pragma once

#include "defs.hpp"
#include "./Renderer.hpp"

class ParticleSystem
{
public:
    ParticleSystem(uint maxParticles, float spawnRadius);
    ~ParticleSystem();

    void Update(float delta);
    void Render(Renderer* renderer);
    void ImGuiRender();

    void SetPos(Float2 pos);
private:
    struct Particle
    {
        float Age;
        float LifeSpan;

        Float3 Position;
        float Rotation;
        Float2 Size;

        Float3 Vel;
        float RVel;

        Float3 Acc;
        float RAcc;

        Float4 Color;
    };

    const uint m_MaxParticles;
    Particle* m_Particles;
    
    Float2 m_Position;
    float m_SpawnRadius;

    float m_MinLifeSpan;
    float m_MaxLifeSpan;

    float m_MinVel;
    float m_MaxVel;

    float m_MinSize;
    float m_MaxSize;
};