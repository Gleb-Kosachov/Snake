//
//  Application.cpp
//  Snake
//
//  Created by Глеб Косачёв on 06/03/2025.
//

#include "Game.hpp"
#include "Apple.hpp"
#include "SnakeBody.hpp"
#include "SnakeHead.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <exception>
#include <cstdlib>

Game::Game(uint32_t FieldSize): FieldSize(FieldSize)
{
    w = std::make_unique<Window>();
    renderer = std::make_unique<Renderer>(FieldSize);
    Field.resize(FieldSize * FieldSize);
    HeadCoords.first = HeadCoords.second = HeadDirection.second = 0;
    HeadDirection.first = 1;
    std::pair<int32_t, int32_t> AppleCoords;
    do {
        AppleCoords.first = std::rand() % FieldSize;
        AppleCoords.second = std::rand() % FieldSize;
    } while (AppleCoords == HeadCoords);
    for (int32_t i = 0; i < FieldSize; i++)
    {
        for (int32_t j = 0; j < FieldSize; j++)
        {
            if (j == HeadCoords.first && i == HeadCoords.second)
                Field[i * FieldSize + j] = new SnakeHead(j, i);
            else if (j == AppleCoords.first && i == AppleCoords.second)
                Field[i * FieldSize + j] = new Apple(j, i);
            else Field[i * FieldSize + j] = new EmptyCell(j, i);
        }
    }
}

Game::~Game()
{
    for (int i = 0; i < Field.size(); i++) delete Field[i];
}

void Game::Run()
{
    std::chrono::high_resolution_clock::time_point Begin = std::chrono::high_resolution_clock::now();
    using namespace std::literals;
    std::chrono::duration Delta(500ms);
    while (!w->ShouldClose() && Running)
    {
        renderer->Clear();
        
        for (Cell *cell : Field)
            cell->OnUpdate(renderer.get());
        renderer->Draw();
        
        if ((std::chrono::high_resolution_clock::now() - Begin) >= Delta)
        {
            Begin = std::chrono::high_resolution_clock::now();
            
            Snake.push(HeadCoords);
            SnakeHead *Head = dynamic_cast<SnakeHead *>(Field[HeadCoords.second * FieldSize + HeadCoords.first]);
            std::pair<int32_t, int32_t> NewDirection = w->GetUserInput();
            while (NewDirection.first || NewDirection.second)
            {
                if (Head->DirectionSuits(NewDirection)) break;
                NewDirection = w->GetUserInput();
            }
            if ((NewDirection.first || NewDirection.second) && Head->DirectionSuits(NewDirection))
                HeadDirection = NewDirection;
            
            Head->Move(HeadDirection);
            Field[HeadCoords.second * FieldSize + HeadCoords.first] = new SnakeBody(HeadCoords.first, HeadCoords.second);
            
            HeadCoords = Head->GetCoords();
            if (HeadCoords.first < 0 || HeadCoords.first >= FieldSize || HeadCoords.second < 0 || HeadCoords.second >= FieldSize) { delete Head; Running = false; }
            if (!Running) break;
            Cell *Encountered = Field[HeadCoords.second * FieldSize + HeadCoords.first];
            Field[HeadCoords.second * FieldSize + HeadCoords.first] = Head;

            std::pair<int32_t, int32_t> Coords;
            switch (Encountered->Collide())
            {
                case CollisionResult::NO_ACTION:
                    Coords = Snake.front();
                    Snake.pop();
                    delete Field[Coords.second * FieldSize + Coords.first];
                    Field[Coords.second * FieldSize + Coords.first] = new EmptyCell(Coords.first, Coords.second);
                    break;
                case CollisionResult::APPLE_EATEN:
                    do {
                        Coords.first = std::rand() % FieldSize;
                        Coords.second = std::rand() % FieldSize;
                    } while (Field[Coords.second * FieldSize + Coords.first]->Collide() != CollisionResult::NO_ACTION);
                    delete Field[Coords.second * FieldSize + Coords.first];
                    Field[Coords.second * FieldSize + Coords.first] = new Apple(Coords.first, Coords.second);
                    break;
                case CollisionResult::GAME_OVER:
                    Running = false;
                    break;
            }
            delete Encountered;
        }
        
        w->UpdateImage();
        w->HandleEvents();
    }
}
