//
//  SnakeBody.hpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#ifndef SnakeBody_hpp
#define SnakeBody_hpp

#include "EmptyCell.hpp"

class SnakeBody : public Cell
{
public:
    SnakeBody(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    CollisionResult Collide() override;
};

#endif /* SnakeBody_hpp */
