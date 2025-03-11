//
//  Apple.cpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#include "Apple.hpp"

Apple::Apple(int32_t x, int32_t y): Cell(x, y) {}

void Apple::OnUpdate(Renderer *r)
{
    r->SetColor(glm::vec3(0.9f, 0.1f, 0.2f));
    r->AddSquare(x, y);
}

CollisionResult Apple::Collide()
{
    return CollisionResult::APPLE_EATEN;
}
