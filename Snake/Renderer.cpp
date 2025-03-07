//
//  Renderer.cpp
//  Snake
//
//  Created by Глеб Косачёв on 06/03/2025.
//

#include "Renderer.hpp"
#include <vector>
#include <glad/gl.h>
#include <sstream>
#include <exception>
#include <cstring>

size_t HashFuncs::operator()(const glm::vec3 &v) const
{
    return std::hash<float>()(v[0]) ^ std::hash<float>()(v[1]) ^ std::hash<float>()(v[2]);
}

bool HashFuncs::operator()(const glm::vec3 &a, const glm::vec3 &b) const
{
    return a == b;
}

bool glCheckErrors()
{
    if (GLenum error = glGetError())
        return true;
    return false;
}

void glClearErrors()
{
    while (glGetError());
}

#define GL_CALL(func)\
glClearErrors();\
func;\
if (glCheckErrors()) {\
std::stringstream ss;\
ss << "OpenGL Error:\nFile: " << __FILE__ << "\nLine: " << __LINE__ << "\nFunction: " << #func;\
throw std::runtime_error(ss.str());\
}

unsigned int CreateShader()
{
    const char *vertex =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 1.0);\n"
        "}\0";
    
    const char *fragment =
        "#version 330 core\n"
        "layout (location = 0) out vec3 color;\n"
        "\n"
        "uniform vec3 Color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = Color;\n"
        "}\0";
    
    GL_CALL(unsigned int result = glCreateProgram());
    GL_CALL(unsigned int vshader = glCreateShader(GL_VERTEX_SHADER));
    GL_CALL(unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER));
    int s = strlen(vertex);
    GL_CALL(glShaderSource(vshader, 1, &vertex, nullptr));
    GL_CALL(glCompileShader(vshader));
    int compiled;
    GL_CALL(glGetShaderiv(vshader, GL_COMPILE_STATUS, &compiled));
    if (compiled == GL_FALSE)
    {
        std::stringstream ss;
        ss << "Error compiling vertex shader!\n";
        int length;
        GL_CALL(glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &length));
        GLchar *msg = new GLchar[length];
        GL_CALL(glGetShaderInfoLog(vshader, length, &length, msg));
        ss << msg << "\n";
        delete[] msg;
        throw std::runtime_error(ss.str());
    }
    s = strlen(fragment);
    GL_CALL(glShaderSource(fshader, 1, &fragment, nullptr));
    GL_CALL(glCompileShader(fshader));
    GL_CALL(glGetShaderiv(fshader, GL_COMPILE_STATUS, &compiled));
    if (compiled == GL_FALSE)
    {
        std::stringstream ss;
        ss << "Error compiling fragment shader!\n";
        int length;
        GL_CALL(glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &length));
        GLchar *msg = new GLchar[length];
        GL_CALL(glGetShaderInfoLog(fshader, length, &length, msg));
        ss << msg << "\n";
        delete[] msg;
        throw std::runtime_error(ss.str());
    }
    GL_CALL(glAttachShader(result, vshader));
    GL_CALL(glAttachShader(result, fshader));
    GL_CALL(glLinkProgram(result));
    GL_CALL(glValidateProgram(result));
    return result;
 }

Renderer::Renderer(uint32_t FieldSize): FieldSize(FieldSize)
{
    std::vector<float> Coords;
    Coords.reserve((FieldSize + 1) * (FieldSize + 1) * 3);
    for (float i = 0; i <= FieldSize; i++)
    {
        for (float j = 0; j <= FieldSize; j++)
        {
            Coords.push_back((j / FieldSize) * 2.0f - 1.0f);
            Coords.push_back((i / FieldSize) * 2.0f - 1.0f);
            Coords.push_back(0.0f);
        }
    }
    GL_CALL(glGenBuffers(1, &VBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, Coords.size() * sizeof(float), Coords.data(), GL_STATIC_DRAW));
    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
    GL_CALL(glEnableVertexAttribArray(0));
    Shader = CreateShader();
    GL_CALL(glUseProgram(Shader));
    GL_CALL(UniformLocation = glGetUniformLocation(Shader, "Color"));
    GL_CALL(glGenBuffers(1, &IBO));
    GL_CALL(glClearColor(0.24f, 0.22f, 0.21f, 1.0f));
}

Renderer::~Renderer()
{
    GL_CALL(glDeleteProgram(Shader));
    GL_CALL(glDeleteVertexArrays(1, &VAO));
    GL_CALL(glDeleteBuffers(1, &VBO));
    GL_CALL(glDeleteBuffers(1, &IBO));
}

void Renderer::SetColor(const glm::vec3 &Color)
{
    this->Color = Color;
}

void Renderer::AddSquare(uint32_t x, uint32_t y)
{
    Squares[Color].emplace(x, y);
}

void Renderer::AddSquareIndices(uint32_t x, uint32_t y)
{
    uint32_t TopLeft = y * (FieldSize + 1) + x;
    uint32_t TopRight = TopLeft + 1;
    uint32_t BottomLeft = (y + 1) * (FieldSize + 1) + x;
    uint32_t BottomRight = BottomLeft + 1;
    Indices.push_back(BottomLeft);
    Indices.push_back(TopRight);
    Indices.push_back(TopLeft);
    Indices.push_back(BottomLeft);
    Indices.push_back(BottomRight);
    Indices.push_back(TopRight);
}

void Renderer::Draw()
{
    for (const std::pair<glm::vec3, std::set<std::pair<uint32_t, uint32_t>>> &MapElement : Squares)
    {
        for (const std::pair<uint32_t, uint32_t> &SetElement : MapElement.second)
            AddSquareIndices(SetElement.first, SetElement.second);
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * 4, Indices.data(), GL_DYNAMIC_DRAW));
        GL_CALL(glBindVertexArray(VAO));
        GL_CALL(glUseProgram(Shader));
        GL_CALL(glUniform3fv(UniformLocation, 1, &MapElement.first[0]));
        GL_CALL(glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr));
        Indices.resize(0);
    }
    Squares.clear();
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
