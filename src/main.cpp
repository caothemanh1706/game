#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// dinh nghia vuot 
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
const int PADDLE_SPEED = 10;

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
void control(){// dieu khien vot
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_w: leftPaddle.dy = -PADDLE_SPEED; break;
            case SDLK_s: leftPaddle.dy = PADDLE_SPEED; break;
            case SDLK_UP: rightPaddle.dy = -PADDLE_SPEED; break;
            case SDLK_DOWN: rightPaddle.dy = PADDLE_SPEED; break;
            }
        }
        else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s: leftPaddle.dy = 0; break;
            case SDLK_UP:
            case SDLK_DOWN: rightPaddle.dy = 0; break;
            }
        }
    }
}
void move() {
    leftPaddle.y += leftPaddle.dy;
    rightPaddle.y += rightPaddle.dy;
   
    ball.x += ball.dx;
    ball.y += ball.dy;
}
void test() {
    if (ball.y <= 0 || ball.y + BALL_SIZE >= SCREEN_HEIGHT) {
        ball.dy = -ball.dy;
    }
    if (leftPaddle.y < 0) leftPaddle.y = 0;
    if (leftPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) leftPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    if (rightPaddle.y < 0) rightPaddle.y = 0;
    if (rightPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) rightPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;

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
       control();
       move();
       test();
       SDL_Delay(15);
    }


    return 0;

}