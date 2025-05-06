#include "game.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
using namespace std;

Paddle leftPaddle, rightPaddle;
Ball ball;
bool running = true;
bool gameStarted = false;
bool gameOver = false;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int BALL_SPEED;
int PADDLE_SPEED;
const float MIN_BALL_SPEED = 3.0f;
const float MAX_BALL_SPEED = 10.0f;
const float MIN_PADDLE_SPEED = 2.0f;
const float MAX_PADDLE_SPEED = 5.0f;
SDL_Texture* imgText = nullptr;
SDL_Rect rect = { 0,0,0,0 };
SDL_Texture* imgText1 = nullptr;
SDL_Rect rect1 = { 0,0,0,0 };
int scoreLeft = 0;
int scoreRight = 0;
TTF_Font* font = nullptr;
TTF_Font* font1 = nullptr;


void initGame() {
    TTF_Init();
    font = TTF_OpenFont("assets/phongchu.ttf", 40);
    font1 = TTF_OpenFont("assets/phongchu.ttf", 20);
    leftPaddle = { 20, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    rightPaddle = { SCREEN_WIDTH - 30, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    BALL_SPEED = MIN_BALL_SPEED;
    ball = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BALL_SPEED, BALL_SPEED };
    PADDLE_SPEED = MAX_PADDLE_SPEED;
    auto* surface = IMG_Load("assets/play.png");
    imgText = SDL_CreateTextureFromSurface(renderer, surface);
    auto* surface1 = IMG_Load("assets/start.png");
    imgText1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_QueryTexture(imgText1, 0, 0, &rect1.w, &rect1.h);
    SDL_QueryTexture(imgText, 0, 0, &rect.w, &rect.h);
}

void control() {// điểu khiển vợt và game
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
            if (event.key.keysym.sym == SDLK_SPACE) {
                if (gameOver) {
                    gameOver = false;
                    scoreLeft = 0;
                    scoreRight = 0;
                    initGame();
                }
                else if (!gameStarted) {
                    gameStarted = true;
                }
            }

            if (gameStarted && !gameOver) {

                switch (event.key.keysym.sym) {
                case SDLK_w: leftPaddle.dy = -PADDLE_SPEED; break;
                case SDLK_s: leftPaddle.dy = PADDLE_SPEED; break;
                case SDLK_UP: rightPaddle.dy = -PADDLE_SPEED; break;
                case SDLK_DOWN: rightPaddle.dy = PADDLE_SPEED; break;
                }
            }
        }
        else if (event.type == SDL_KEYUP && gameStarted && !gameOver) {
            switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s: leftPaddle.dy = 0; break;
            case SDLK_UP:
            case SDLK_DOWN: rightPaddle.dy = 0; break;
            }
        }
    }
}

void resetGameState(bool scoredByLeft) {//hàm khởi tạo lại trạng thái game sau khi có điểm
    BALL_SPEED = MIN_BALL_SPEED;
    PADDLE_SPEED = MAX_PADDLE_SPEED;
    leftPaddle = { 20, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    rightPaddle = { SCREEN_WIDTH - 30, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2, 0 };
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.dx = scoredByLeft ? BALL_SPEED : -BALL_SPEED;
    ball.dy = BALL_SPEED; 
}

void move() {  // hàm di chuyển bóng vợt ;
    if (gameOver || !gameStarted) return;
    leftPaddle.y += leftPaddle.dy;
    rightPaddle.y += rightPaddle.dy;

    ball.x += ball.dx;
    ball.y += ball.dy;
}

void test() {//kiểm tra va chạm vợt ,bóng với tường
    if (ball.y <= 0 || ball.y + BALL_SIZE >= SCREEN_HEIGHT) {
        ball.dy = -ball.dy; 
    }
    if (leftPaddle.y < 0) leftPaddle.y = 0;
    if (leftPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) leftPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    if (rightPaddle.y < 0) rightPaddle.y = 0;
    if (rightPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) rightPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void update() {// kiểm tra va chạm bóng với vợt và cải tiến
    if (ball.x <= leftPaddle.x + PADDLE_WIDTH && ball.x >= leftPaddle.x &&
        ball.y + BALL_SIZE >= leftPaddle.y && ball.y <= leftPaddle.y + PADDLE_HEIGHT) {
        ball.dx = -ball.dx; 
        ball.x = leftPaddle.x + PADDLE_WIDTH;
        ball.dx *= 1.4;
        ball.dy *= 1.4;
        if (abs(ball.dx) > MAX_BALL_SPEED) ball.dx = (ball.dx > 0) ? MAX_BALL_SPEED : -MAX_BALL_SPEED;
        if (abs(ball.dy) > MAX_BALL_SPEED) ball.dy = (ball.dy > 0) ? MAX_BALL_SPEED : -MAX_BALL_SPEED;
        PADDLE_SPEED *= 0.8;
        if (PADDLE_SPEED < MIN_PADDLE_SPEED) PADDLE_SPEED = MIN_PADDLE_SPEED;
    }
    if (ball.x + BALL_SIZE >= rightPaddle.x &&
        ball.x + BALL_SIZE <= rightPaddle.x + PADDLE_WIDTH &&
        ball.y + BALL_SIZE >= rightPaddle.y && ball.y <= rightPaddle.y + PADDLE_HEIGHT) {
        ball.dx = -ball.dx;
        ball.x = rightPaddle.x - BALL_SIZE;
        ball.dx *= 1.4;
        ball.dy *= 1.4;
        if (abs(ball.dx) > MAX_BALL_SPEED) ball.dx = (ball.dx > 0) ? MAX_BALL_SPEED : -MAX_BALL_SPEED;
        if (abs(ball.dy) > MAX_BALL_SPEED) ball.dy = (ball.dy > 0) ? MAX_BALL_SPEED : -MAX_BALL_SPEED;
        PADDLE_SPEED *= 0.8;
        if (PADDLE_SPEED < MIN_PADDLE_SPEED) PADDLE_SPEED = MIN_PADDLE_SPEED;
    }
    if (ball.x < 0) {
        scoreRight++;
        if (scoreRight == 5) {
            gameOver = true;
        }
        resetGameState(false);
    }
    else if (ball.x > SCREEN_WIDTH) {
        scoreLeft++;
        if (scoreLeft == 5) {
            gameOver = true;
        }
        resetGameState(true);
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 55, 55, 255);
    SDL_RenderClear(renderer);

    if (gameOver) {
        string winner = (scoreLeft >= 3) ? "PLAYER LEFT WIN" : "PLAYER RIGHT WIN";

        auto* surface = TTF_RenderText_Solid(font, winner.c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
        auto* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int w, h;
        SDL_QueryTexture(texture, 0, 0, &w, &h);
        SDL_Rect rect = { (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        surface = TTF_RenderText_Solid(font1, "Press SPACE to restart", { 0xFF, 0xFF, 0xFF, 0xFF });
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, 0, 0, &w, &h);
        rect = { (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 + 50, w, h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        surface = TTF_RenderText_Solid(font1, "Press ESC to quit", { 0xFF, 0xFF, 0xFF, 0xFF });
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, 0, 0, &w, &h);
        rect = { (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 + 100, w, h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
        return;
    }

    if (!gameStarted) {
        SDL_RenderCopy(renderer, imgText1, nullptr, nullptr);

        auto* surface = TTF_RenderText_Solid(font1, "Press SPACE to start", { 0xFF, 0xFF, 0xFF, 0xFF });
        auto* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int w, h;
        SDL_QueryTexture(texture, 0, 0, &w, &h);
        SDL_Rect rect = { (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2 + 200, w, h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        surface = TTF_RenderText_Solid(font1, "W/S: Move Left Paddle      |     UP/DOWN: Move Right Paddle", { 0xFF, 0xFF, 0xFF, 0xFF });
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, 0, 0, &w, &h);
        rect = { (SCREEN_WIDTH - w) / 2, SCREEN_HEIGHT - 50, w, h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    else {
        SDL_RenderCopy(renderer, imgText, nullptr, nullptr);

        // Vẽ đường kẻ giữa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int y = 0; y < SCREEN_HEIGHT; y += 10) {
            SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, y);
        }

        // Vẽ vợt và bóng
        SDL_Rect leftPaddleRect = { leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_Rect rightPaddleRect = { rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_Rect ballRect = { ball.x, ball.y, BALL_SIZE, BALL_SIZE };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &leftPaddleRect);
        SDL_RenderFillRect(renderer, &rightPaddleRect);
        SDL_RenderFillRect(renderer, &ballRect);

        // Hiển thị điểm số
        auto* surface = TTF_RenderText_Solid(font, (to_string(scoreLeft) + " / 5").c_str(), { 255, 255, 255, 255 });
        auto* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int w, h;
        SDL_QueryTexture(texture, 0, 0, &w, &h);
        SDL_Rect rect = { SCREEN_WIDTH / 4 - w / 2, 20, w, h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        surface = TTF_RenderText_Solid(font, (to_string(scoreRight) + " / 5").c_str(), { 255, 255, 255, 255 });
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, 0, 0, &w, &h);
        rect = { 3 * SCREEN_WIDTH / 4 - w / 2, 20, w, h };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}
