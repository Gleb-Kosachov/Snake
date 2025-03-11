//
//  SnakeBody.cpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#include "SnakeBody.hpp"

SnakeBody::SnakeBody(int32_t x, int32_t y): Cell(x, y) {}

void SnakeBody::OnUpdate(Renderer *r)
{
    r->SetColor(glm::vec3(0.1f, 0.6f, 0.2f));
    r->AddSquare(x, y);
}

CollisionResult SnakeBody::Collide()
{
    return CollisionResult::GAME_OVER;
}
