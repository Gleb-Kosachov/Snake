//
//  main.cpp
//  Snake
//
//  Created by Глеб Косачёв on 06/03/2025.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.hpp"

int main(int argc, const char * argv[]) {
    std::srand(std::time(NULL));
    try
    {
        Game game;
        game.Run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::abort();
    }
    return 0;
}
