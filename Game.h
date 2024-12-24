//
// Created by SKY on 2024/12/24.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <deque>

const int GRIDCOUNT = 30;
const int GRIDLENGHT = 25;
const Color green = {173,204,96,255};
const Color darkGreen = {43,51,24,255};

struct Food{
    Vector2 pos;
    bool isExist;
};
struct Snake{
    std::deque<Vector2> body;
    bool isExist;
    Vector2 dir;
};

class Game {
public:
    Game();
    ~Game();
    int Run();
private:
    int Update();
    int Draw();
    int Init();
    Snake snake;
    Food food;
    double lastTimOfUpdate;
    double currentTime;
    int offset;
    int score;
};


#endif //SNAKE_GAME_H
