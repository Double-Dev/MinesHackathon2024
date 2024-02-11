#include "Renderer.hpp"

#include <iostream>

#include "window/Window.hpp"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>

Renderer::Renderer() : m_MaxQuads(1000000), m_MaxVertices(m_MaxQuads * 4), m_MaxBytes(m_MaxQuads * 4 * sizeof(Vertex2D))
{
    // ImGui Initialization
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Window::Instance()->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 410");

    GLint isCompiled;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSource = 
        "#version 410 core\n"
        "layout (location = 0) in vec3 a_position;\n"
        "layout (location = 1) in vec4 a_color;\n"
        "out vec4 v_color;\n"
        "void main()\n"
        "{\n"
        "   v_color = a_color;\n"
        "   gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);\n"
        "}\0";
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(vertexShader, infoLogLength, &infoLogLength, infoLog);
        std::cout << infoLog << std::endl;
    }

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragSource = 
        "#version 410 core\n"
        "in vec4 v_color;\n"
        "out vec4 o_color;\n"
        "void main()\n"
        "{\n"
        "   o_color = v_color;\n"
        "}\0";
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(vertexShader, infoLogLength, &infoLogLength, infoLog);
        std::cout << infoLog << std::endl;
    }
    
    m_Shader = glCreateProgram();
    glAttachShader(m_Shader, vertexShader);
    glAttachShader(m_Shader, fragShader);
    glLinkProgram(m_Shader);
    GLint isLinked;
    glGetProgramiv(m_Shader, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
        std::cout << "NOOOOOO" << std::endl;

    glDetachShader(m_Shader, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(m_Shader, fragShader);
    glDeleteShader(fragShader);

    m_PositionsBuffer[0] = { -1.0f, -1.0f, 0.0f, 1.0f };
    m_PositionsBuffer[1] = {  1.0f, -1.0f, 0.0f, 1.0f };
    m_PositionsBuffer[2] = {  1.0f,  1.0f, 0.0f, 1.0f };
    m_PositionsBuffer[3] = { -1.0f,  1.0f, 0.0f, 1.0f };

    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);

    uint* indices = new uint[m_MaxQuads*6];
    for (uint i = 0 ; i < m_MaxQuads; i++)
    {
        indices[(i*6)]   = (i*4);
        indices[(i*6)+1] = (i*4)+1;
        indices[(i*6)+2] = (i*4)+2;
        indices[(i*6)+3] = (i*4)+2;
        indices[(i*6)+4] = (i*4)+3;
        indices[(i*6)+5] = (i*4);
    }
    glCreateBuffers(1, &m_Ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * m_MaxQuads*6, indices, GL_STATIC_DRAW);
    delete[] indices;
    
    m_Buffer = new Vertex2D[m_MaxVertices];
    m_BufferPtr = m_Buffer;
    m_NumQuads = 0;

    glCreateBuffers(1, &m_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, m_MaxBytes, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)(3 * sizeof(float)));
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Ibo);
    glDeleteBuffers(1, &m_Vbo);

    glDeleteProgram(m_Shader);

    delete[] m_Buffer;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::SetCamera(const Mat4& camera)
{

}

void Renderer::SetClearColor(const Float4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DrawQuad(const Float3& position, const Float2& scale, const Float4& color)
{
    DrawQuad(glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), { scale.x, scale.y, 0.0f }), color);
}

void Renderer::DrawQuad(const Float3& position, const float rotation, const Float2& scale, const Float4& color)
{
    DrawQuad(glm::translate(Mat4(1.0f), position) * glm::rotate(Mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(Mat4(1.0f), { scale.x, scale.y, 0.0f }), color);
}

void Renderer::DrawQuad(const Mat4& transform, const Float4& color)
{
    if (m_NumQuads >= m_MaxQuads)
        Render();
    for (size_t i = 0; i < 4; i++)
    {
        m_BufferPtr->Position = transform * m_PositionsBuffer[i];
        m_BufferPtr->Color = color;
        m_BufferPtr++;
    }
    m_NumQuads++;
}

void Renderer::DrawSprite(const Float3& position, const float rotation, const Float2& scale)
{

}

void Renderer::Render()
{
    // Batch Rendering
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_NumQuads * 4 * sizeof(Vertex2D), m_Buffer);
    
    glUseProgram(m_Shader);
    glBindVertexArray(m_Vao);
    glDrawElements(GL_TRIANGLES, m_NumQuads * 6, GL_UNSIGNED_INT, nullptr);
    m_BufferPtr = m_Buffer;
    m_NumQuads = 0;
}

void Renderer::BeginImGuiRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::EndImGuiRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
