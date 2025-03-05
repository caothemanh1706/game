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

void intiGame() {  // thiet lap vi tri ban dau cua vot va bong
    leftPaddle = { 20, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    rightPaddle = { 20 , (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2,0 };
    ball = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BALL_SPEED, BALL_SPEED };
}

