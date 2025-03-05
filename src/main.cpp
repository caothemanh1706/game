#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// dinh nghia vuot 
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
const int PADDLE_SPEED = 5;

// dinh nghia qua bong
const int BALL_SIZE = 10;
const int BALL_SPEED = 4;

struct Paddle {
    int x, y;
    int dy;
};

struct Ball {
    int x, y;
    int dx, dy;
};
Paddle leftPaddle, rightPaddle;
Ball ball;
// khoi tao sdl 
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;

void initGame() {  // thiet lap vi tri ban dau cua vot va bong
    leftPaddle = { 20, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    rightPaddle = { SCREEN_WIDTH - 30, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2,0 };
    ball = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BALL_SPEED, BALL_SPEED };
}

int SDL_main(int argc, char* argv[]) {

    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    initGame();

    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 55, 55, 255); //màu nền xanh thẩm
        SDL_RenderClear(renderer);

       
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
        SDL_Rect leftPaddleRect = { leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_RenderFillRect(renderer, &leftPaddleRect);

        SDL_Rect rightPaddleRect = { rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_RenderFillRect(renderer, &rightPaddleRect);
        SDL_Rect ballRect = { ball.x,ball.y,BALL_SIZE,BALL_SIZE };
        SDL_RenderFillRect(renderer, &ballRect);

       SDL_RenderPresent(renderer); 
    }


    return 0;

}