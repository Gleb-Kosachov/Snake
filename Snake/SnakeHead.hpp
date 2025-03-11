//
//  SnakeHead.hpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#ifndef SnakeHead_hpp
#define SnakeHead_hpp

#include "SnakeBody.hpp"

class SnakeHead : public SnakeBody
{
    int32_t PrevX = INT32_MAX, PrevY = INT32_MAX;
public:
    SnakeHead(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    void Move(const std::pair<int32_t, int32_t> &);
    bool DirectionSuits(const std::pair<int32_t, int32_t> &);
};

#endif /* SnakeHead_hpp */
