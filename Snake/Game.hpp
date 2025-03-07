//
//  Application.hpp
//  Snake
//
//  Created by Глеб Косачёв on 06/03/2025.
//

#ifndef Application_hpp
#define Application_hpp

#include <cstdint>
#include <queue>
#include <vector>
#include <memory>
#include "Window.hpp"
#include "Renderer.hpp"
#include "Cell.hpp"

class Game
{
    bool Running = true;
    std::unique_ptr<Window> w;
    std::unique_ptr<Renderer> renderer;
    uint32_t FieldSize;
    std::vector<Cell *> Field;
    std::pair<int32_t, int32_t> HeadCoords;
    std::pair<int32_t, int32_t> HeadDirection;
    std::queue<std::pair<int32_t, int32_t>> Snake;
public:
    Game(uint32_t = 10);
    ~Game();
    
    void Run();
};

#endif /* Application_hpp */
