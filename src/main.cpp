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

