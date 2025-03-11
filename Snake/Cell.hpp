//
//  Cell.hpp
//  Snake
//
//  Created by Глеб Косачёв on 07/03/2025.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <cstdint>
#include "Renderer.hpp"

enum class CollisionResult{ NO_ACTION = 0, APPLE_EATEN, GAME_OVER };

class Cell
{
protected:
    int32_t x, y;
public:
    Cell(int32_t, int32_t);
    virtual void OnUpdate(Renderer *) = 0;
    virtual CollisionResult Collide() = 0;
    
    inline std::pair<int32_t, int32_t> GetCoords() { return std::make_pair(x, y); }
};

#endif /* Cell_hpp */
