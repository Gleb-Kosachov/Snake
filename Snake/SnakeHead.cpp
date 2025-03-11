//
//  SnakeHead.cpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#include "SnakeHead.hpp"

SnakeHead::SnakeHead(int32_t x, int32_t y): SnakeBody(x, y) {}

void SnakeHead::OnUpdate(Renderer *r)
{
    r->SetColor(glm::vec3(0.5f, 0.9f, 0.2f));
    r->AddSquare(x, y);
}

void SnakeHead::Move(const std::pair<int32_t, int32_t> &Direction)
{
    PrevX = x;
    PrevY = y;
    x += Direction.first;
    y += Direction.second;
}

bool SnakeHead::DirectionSuits(const std::pair<int32_t, int32_t> &Direction)
{
    return x + Direction.first != PrevX || y + Direction.second != PrevY;
}
