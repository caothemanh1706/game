#include "game.h"
#include <iostream>
#include<SDL2/SDL_image.h>
using namespace std;


Paddle leftPaddle, rightPaddle;
Ball ball;
bool running = true;
bool gameStarted = false;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int BALL_SPEED = 4;
int PADDLE_SPEED = 5;
const float MIN_BALL_SPEED = 4.0f;
const float MAX_BALL_SPEED = 10.0f;
const float MIN_PADDLE_SPEED = 2.0f;
const float MAX_PADDLE_SPEED = 5.0f;
SDL_Texture* imgText = nullptr;
SDL_Rect rect = { 0, 0, 0, 0 };
SDL_Texture* imgText1 = nullptr;
SDL_Rect rect1 = { 0,0,0,0 };

void initGame() {
    leftPaddle = { 20, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    rightPaddle = { SCREEN_WIDTH - 30, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    ball = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BALL_SPEED, BALL_SPEED };
    BALL_SPEED = MIN_BALL_SPEED;
    PADDLE_SPEED = MAX_PADDLE_SPEED;
    ball.dx = (rand() % 2 == 0) ? BALL_SPEED : -BALL_SPEED;
    ball.dy = (rand() % 2 == 0) ? BALL_SPEED : -BALL_SPEED;

    auto* surface = IMG_Load("assets/play.png");
    imgText = SDL_CreateTextureFromSurface(renderer, surface);
    auto* surface1 = IMG_Load("assets/start.png");
    imgText1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_QueryTexture(imgText1, 0, 0, &rect1.w, &rect1.h);

    SDL_QueryTexture(imgText, 0, 0, &rect.w, &rect.h);
}
void control() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (!gameStarted && event.key.keysym.sym == SDLK_SPACE) {
                gameStarted = true;
                return;
            }

            if (gameStarted) {
                switch (event.key.keysym.sym) {
                case SDLK_w: leftPaddle.dy = -PADDLE_SPEED; break;
                case SDLK_s: leftPaddle.dy = PADDLE_SPEED; break;
                case SDLK_UP: rightPaddle.dy = -PADDLE_SPEED; break;
                case SDLK_DOWN: rightPaddle.dy = PADDLE_SPEED; break;
                }
            }
        }
        else if (event.type == SDL_KEYUP && gameStarted) {
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
    ball.x -= ball.dx;
    ball.y -= ball.dy;
}
void test() {
    if (ball.y <= 0 || ball.y + BALL_SIZE >= SCREEN_HEIGHT) {
        ball.dy = -ball.dy;
        ball.dx *= 1.2;
        ball.dy *= 1.2;
        if (abs(ball.dx) > MAX_BALL_SPEED) {
            ball.dx = (ball.dx > 0) ? MAX_BALL_SPEED : -MAX_BALL_SPEED;
        }
        if (abs(ball.dy) > MAX_BALL_SPEED) {
            ball.dy = (ball.dy > 0) ? MAX_BALL_SPEED : -MAX_BALL_SPEED;
        }
    }

    if (leftPaddle.y < 0) leftPaddle.y = 0;
    if (leftPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) leftPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    if (rightPaddle.y < 0) rightPaddle.y = 0;
    if (rightPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) rightPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}
void update() {
    if (ball.x <= leftPaddle.x + PADDLE_WIDTH &&
        ball.x >= leftPaddle.x &&
        ball.y + BALL_SIZE >= leftPaddle.y &&
        ball.y <= leftPaddle.y + PADDLE_HEIGHT) {
        ball.dx = -ball.dx;
        PADDLE_SPEED *= 0.9;
        if (PADDLE_SPEED < MIN_PADDLE_SPEED) {
            PADDLE_SPEED = MIN_PADDLE_SPEED;
        }
        ball.x = leftPaddle.x + PADDLE_WIDTH;
    }
        if (ball.x + BALL_SIZE >= rightPaddle.x &&
        ball.x + BALL_SIZE <= rightPaddle.x + PADDLE_WIDTH &&
        ball.y + BALL_SIZE >= rightPaddle.y &&
        ball.y <= rightPaddle.y + PADDLE_HEIGHT) {
        ball.dx = -ball.dx;
        PADDLE_SPEED *= 0.9;
        if (PADDLE_SPEED < MIN_PADDLE_SPEED) {
            PADDLE_SPEED = MIN_PADDLE_SPEED;
        }
        ball.x = rightPaddle.x - BALL_SIZE;
    }
    if (ball.x < 0 || ball.x > SCREEN_WIDTH) {
        ball.x = SCREEN_WIDTH / 2;
        ball.y = SCREEN_HEIGHT / 2;
        BALL_SPEED = MIN_BALL_SPEED;
      
        ball.dx = (rand() % 2 == 0) ? BALL_SPEED : -BALL_SPEED;
        ball.dy = (rand() % 2 == 0) ? BALL_SPEED : -BALL_SPEED;
    }
}
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 55, 55, 255);
    SDL_RenderClear(renderer);

    if (!gameStarted) {
        SDL_RenderCopy(renderer, imgText1, 0, 0);  
        SDL_RenderPresent(renderer);
        return;
    }
    else {

        SDL_RenderCopy(renderer, imgText, 0, 0);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            if (y % 5 == 0) {
                SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, y);
            }
        }

        SDL_Rect leftPaddleRect = { leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_RenderFillRect(renderer, &leftPaddleRect);

        SDL_Rect rightPaddleRect = { rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_RenderFillRect(renderer, &rightPaddleRect);

        SDL_Rect ballRect = { ball.x, ball.y, BALL_SIZE, BALL_SIZE };
        SDL_RenderFillRect(renderer, &ballRect);

        SDL_RenderPresent(renderer);
    }
}
