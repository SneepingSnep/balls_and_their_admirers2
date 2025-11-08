#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#define WIDTH 800
#define HEIGHT 800
#define TITLE "Balls and their admirers"
#define BALL_COUNT 100
#define FPS 60
#define VEL_MAX 5
#define RADIUS_MAX 30
#define RADIUS_MIN 15

Color COLORS[] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN,
};
size_t corlorsCount = _countof(COLORS);
struct Ball {
  int posx, posy, velx, vely;
  int radius;
  Color color;
  struct Ball *follows;
};
typedef struct Ball Ball;
// Definition of Ball
// Ball stores state and other properties
// YOUR CODE HERE
Ball balls[BALL_COUNT];

// Initializes a ball with random values
Ball *init_ball_random(Ball *p) {
  // Randomly initialize state and properties
  // YOUR CODE HERE

  p->color = COLORS[rand() % corlorsCount];
  p->posx = rand() % WIDTH;
  p->posy = rand() % HEIGHT;
  p->radius = rand() % (RADIUS_MAX - RADIUS_MIN + 1);
  p->velx = rand() % VEL_MAX;
  p->vely = rand() % VEL_MAX;

  // Find a leading ball other than the initialized ball itself.
  Ball *leader; // Represents the leading ball that this ball will follow
                // YOUR CODE HERE
  leader = &balls[rand() % BALL_COUNT];

  p->follows = leader;
  return p;
}

// Initialize all `balls`
void init_balls_random() {
  for (size_t count = 0; count < BALL_COUNT; count++) {
    Ball initball;
    init_ball_random(&initball);
    balls[count] = initball;
  }
}

Ball *draw_ball(Ball *p) {
  DrawCircle(p->posx, p->posy, p->radius, p->color);
  return p;
}

// Updates the positions of balls according to their velocities
Ball *update_pos(Ball *p) {
  p->posx = (WIDTH + p->posx + p->velx) %
            WIDTH; // `WIDTH +` because C uses truncated division
  p->posy = (HEIGHT + p->posy + p->vely) % HEIGHT;
  return p;
}

// Updates the velocity of a ball so that it follows the leading ball
Ball *update_vel_for_following(Ball *p) {
  int errx = p->follows->posx - p->posx;
  int erry = p->follows->posy - p->posy;
  p->velx = errx > 0 ? 1 : -1;
  p->vely = erry > 0 ? 1 : -1;
  return p;
}

// Update all elements
void update_elements() {
  for (size_t i = 0; i < _countof(balls); ++i) {
    draw_ball(update_pos(update_vel_for_following(&balls[i])));
  }
}

int main() {
  // james.color = COLORS[1];
  // Color color = COLORS[5];
  // printf("%zu", _countof(balls));
  // printf("%zu", _countof(COLORS));
  srand(time(NULL));
  // return 0;
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);
  init_balls_random();
  // draw_ball(&biggieTheBlueBall);
  //  draw_ball(init_ball_random(&biggieTheBlueBall));

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    update_elements();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}