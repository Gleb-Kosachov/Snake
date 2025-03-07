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

enum class CollisionResult{ NO_ACTION = 0, APPLE_EATEN, GAME_OVER, NOT_APPLICABLE };

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

class EmptyCell : public Cell
{
public:
    EmptyCell(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    CollisionResult Collide() override;
};

class Apple : public Cell
{
public:
    Apple(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    CollisionResult Collide() override;
};

class SnakeBody : public Cell
{
public:
    SnakeBody(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    CollisionResult Collide() override;
};

class SnakeHead : public SnakeBody
{
    int32_t PrevX = INT32_MAX, PrevY = INT32_MAX;
public:
    SnakeHead(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    CollisionResult Collide() override;
    void Move(const std::pair<int32_t, int32_t> &);
    bool DirectionSuits(const std::pair<int32_t, int32_t> &);
};

#endif /* Cell_hpp */
