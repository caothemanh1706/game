#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int PADDLE_WIDTH = 10;

const int PADDLE_HEIGHT=100;
extern int PADDLE_SPEED ;


const int BALL_SIZE = 10;
extern int BALL_SPEED;


struct Paddle {
    int x, y;
    int dy;
};

struct Ball {
    int x, y;
    int dx, dy;
};
extern Paddle leftPaddle, rightPaddle;
extern Ball ball;
extern bool running;
extern SDL_Window* window;
extern SDL_Renderer* renderer;


void initGame();
void control();
void move();
void test();
void update();
void render();

#endif
