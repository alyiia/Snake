//
// Created by SKY on 2024/12/24.
//

#include "Game.h"

Game::Game() {

}

Game::~Game() {

}

int Game::Run() {
    Init();

    while(WindowShouldClose() == false){
        Update();
        Draw();
    }

    CloseWindow();
}

int Game::Init() {
    srand(time(0));
    offset = 75;
    score = 0;

    food.pos = {0,0};
    food.isExist = false;
    snake.body.push_back(Vector2{0,0});
    snake.isExist = false;
    snake.dir = Vector2{1,0};
    InitWindow(GRIDCOUNT*GRIDLENGHT+2*offset,GRIDCOUNT*GRIDLENGHT+2*offset, "Snake!!");
    SetTargetFPS(30);

    lastTimOfUpdate = GetTime();
    currentTime = GetTime();


    return 0;
}

int Game::Update() {
    //Set the position of food and snake
    if(!food.isExist){
        food.pos.x = rand() % GRIDCOUNT;
        food.pos.y = rand() % GRIDCOUNT;
        food.isExist = true;
    }
    if(!snake.isExist){
        snake.body.clear();
        snake.body.push_front(Vector2{0,0});
        snake.body.front().x = rand() % GRIDCOUNT;
        snake.body.front().y = rand() % GRIDCOUNT;
        snake.isExist = true;
    }

    currentTime = GetTime();

    //方向更改
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && !Vector2Equals(snake.dir, Vector2{1, 0}))
        snake.dir = Vector2{-1, 0};
    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && !Vector2Equals(snake.dir, Vector2{-1, 0}))
        snake.dir = Vector2{1, 0};
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && !Vector2Equals(snake.dir, Vector2{0, 1}))
        snake.dir = Vector2{0, -1};
    if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && !Vector2Equals(snake.dir, Vector2{0, -1}))
        snake.dir = Vector2{0, 1};


    //位置更新
    if (snake.isExist && !Vector2Equals(snake.dir, Vector2 {0,0}) && (currentTime - lastTimOfUpdate) > 0.2) {
        snake.body.push_front(Vector2Add(snake.body[0], snake.dir));

        //吃食物与增长
        if(Vector2Equals(snake.body[0], food.pos)){
            food.isExist = false;
            score++;
        }else{
            snake.body.pop_back();
        }

        //检测是否到边界
        if(snake.body.front().x >= GRIDCOUNT || snake.body.front().x <= 0-1
                || snake.body.front().y >= GRIDCOUNT || snake.body.front().y <= 0-1){
            snake.isExist = false;
            score = 0;
        }
        //检测是否碰撞到自己
        for (int i = 1; i < snake.body.size(); ++i) {
            if(Vector2Equals(snake.body[0], snake.body[i])){
                score = 0;
                snake.isExist = false;
            }


        }
        lastTimOfUpdate = currentTime;
    }

    return 0;
}

int Game::Draw() {
    BeginDrawing();

    //Draw Background
    ClearBackground(green);

    DrawRectangleLinesEx(Rectangle{(float)offset-5, (float )offset-5, (float)GRIDCOUNT*GRIDLENGHT+10, (float)GRIDCOUNT*GRIDLENGHT+10}, 5,darkGreen);
    DrawText("Snake!!", offset-5, 20,40, darkGreen);
    DrawText(TextFormat("%i", score), offset+GRIDLENGHT*GRIDCOUNT - 100, 20,40, darkGreen);
    //Draw Food
    DrawRectangleRounded(Rectangle{offset+food.pos.x*GRIDLENGHT, offset+food.pos.y*GRIDLENGHT, GRIDLENGHT, GRIDLENGHT,}, 0.5, 0, darkGreen);

    //Draw Game
    for(auto i : snake.body){
        DrawRectangle(offset+i.x*GRIDLENGHT, offset+i.y*GRIDLENGHT, GRIDLENGHT,GRIDLENGHT, darkGreen);
    }

    EndDrawing();

    return 0;
}