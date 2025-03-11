//
//  EmptyCell.cpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#include "EmptyCell.hpp"

EmptyCell::EmptyCell(int32_t x, int32_t y): Cell(x, y) {}
void EmptyCell::OnUpdate(Renderer *r) {}
CollisionResult EmptyCell::Collide()
{
    return CollisionResult::NO_ACTION;
}
