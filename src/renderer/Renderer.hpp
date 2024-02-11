#pragma once

#include "defs.hpp"
#include <glad/glad.h>

#include "imgui.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void SetCamera(const Mat4& camera);
    void SetClearColor(const Float4& color);

    void Clear();

    void DrawQuad(const Float3& position, const Float2& scale, const Float4& color);
    void DrawQuad(const Float3& position, const float rotation, const Float2& scale, const Float4& color);
    void DrawQuad(const Mat4& transform, const Float4& color);
    void DrawSprite(const Float3& position, const float rotation, const Float2& scale);

    void Render();
    void BeginImGuiRender();
    void EndImGuiRender();
private:
    const uint m_MaxQuads;
    const uint m_MaxVertices;
    const uint m_MaxBytes;
    struct Vertex2D {
        Float3 Position;
        Float4 Color;
    };
    Vertex2D* m_Buffer;
    Vertex2D* m_BufferPtr;
    Float4 m_PositionsBuffer[4];
    uint m_NumQuads = 0;
    
    Mat4 m_CameraMat;

    GLuint m_Vao;
    GLuint m_Ibo;
    GLuint m_Vbo;

    GLuint m_Shader;
};
