//
//  Renderer.hpp
//  Snake
//
//  Created by Глеб Косачёв on 06/03/2025.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <set>

struct HashFuncs
{
    size_t operator()(const glm::vec3 &) const;
    bool operator()(const glm::vec3 &, const glm::vec3 &) const;
};

class Renderer
{
    uint32_t FieldSize;
    uint32_t VBO;
    uint32_t IBO;
    uint32_t VAO;
    uint32_t Shader;
    uint32_t UniformLocation;
    glm::vec3 Color;
    std::vector<uint32_t> Indices;
    std::unordered_map<glm::vec3, std::set<std::pair<uint32_t, uint32_t>>, HashFuncs, HashFuncs> Squares;
    void AddSquareIndices(uint32_t, uint32_t);
public:
    Renderer(uint32_t);
    ~Renderer();
    void SetColor(const glm::vec3 &Color);
    void AddSquare(uint32_t x, uint32_t y);
    void Draw();
    void Clear();
};

#endif /* Renderer_hpp */
