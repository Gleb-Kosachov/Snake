//
//  Cell.cpp
//  Snake
//
//  Created by Глеб Косачёв on 07/03/2025.
//

#include "Cell.hpp"

Cell::Cell(int32_t x, int32_t y): x(x), y(y) {}

EmptyCell::EmptyCell(int32_t x, int32_t y): Cell(x, y) {}
Apple::Apple(int32_t x, int32_t y): Cell(x, y) {}
SnakeBody::SnakeBody(int32_t x, int32_t y): Cell(x, y) {}
SnakeHead::SnakeHead(int32_t x, int32_t y): SnakeBody(x, y) {}


void EmptyCell::OnUpdate(Renderer *r) {}
void Apple::OnUpdate(Renderer *r)
{
    r->SetColor(glm::vec3(0.9f, 0.1f, 0.2f));
    r->AddSquare(x, y);
}
void SnakeBody::OnUpdate(Renderer *r)
{
    r->SetColor(glm::vec3(0.1f, 0.6f, 0.2f));
    r->AddSquare(x, y);
}
void SnakeHead::OnUpdate(Renderer *r)
{
    r->SetColor(glm::vec3(0.5f, 0.9f, 0.2f));
    r->AddSquare(x, y);
}

CollisionResult EmptyCell::Collide() { return CollisionResult::NO_ACTION; }
CollisionResult Apple::Collide() { return CollisionResult::APPLE_EATEN; }
CollisionResult SnakeBody::Collide() { return CollisionResult::GAME_OVER; }
CollisionResult SnakeHead::Collide() { return CollisionResult::NOT_APPLICABLE; }

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
