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
#define BALL_COUNT 50
#define FPS 60
#define VEL_MAX 5
#define RADIUS_MAX 30
#define RADIUS_MIN 15
#define SHAPECOUNT 100
enum Type { ball, square };
Color COLORS[] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN,
};
size_t corlorsCount = _countof(COLORS);
size_t globalcountforballs = 0;
struct Ball {
  int posx, posy, velx, vely;
  int radius;
  Color color;
  struct Ball *follows;
};
struct Rectangleshape {
  int posx, posy, velx, vely;
  int radius;
  Color color;
  struct Ball *follows;
};

typedef struct Rectangleshape Rectangleshape;
typedef struct Ball Ball;
union Shape {
  Ball ball;
  Rectangleshape rectangle;
};
typedef union Shape Shape;
struct figure {
  enum Type type;
  Shape shape;
};

Ball balls[BALL_COUNT];
Rectangleshape rectangles[BALL_COUNT];
struct figure figuresshape[SHAPECOUNT];

struct figure shape1 = {.type = 2};

struct figure *init_shape_random(struct figure *p, int shapenumber) {
  if (p->type == 0) {
    p->shape.ball.color = COLORS[rand() % corlorsCount];
    p->shape.ball.posx = rand() % WIDTH;
    p->shape.ball.posy = rand() % HEIGHT;
    p->shape.ball.radius = (RADIUS_MAX - RADIUS_MIN + 1);
    p->shape.ball.velx = 0;
    p->shape.ball.vely = 0;
  } else if (p->type == 1) {
    p->shape.rectangle.color = COLORS[rand() % corlorsCount];
    p->shape.rectangle.posx = rand() % WIDTH;
    p->shape.rectangle.posy = rand() % HEIGHT;
    p->shape.rectangle.radius = (RADIUS_MAX - RADIUS_MIN + 1);
    p->shape.rectangle.velx = rand() % VEL_MAX;
    p->shape.rectangle.vely = rand() % VEL_MAX;
    int index;
    do {
      index = rand() % BALL_COUNT;
    } while (figuresshape[index].type != ball);
    p->shape.rectangle.follows = &figuresshape[index].shape.ball;
  }
  return p;
}

void init_balls_random() {
  int shapenumber;
  int counterB = 0;
  for (size_t count = 0; count < BALL_COUNT; count++) {
    struct figure initshape;
    if ((count % 2) == 0) {
      shapenumber = 0;
      initshape.type = 0;
      init_shape_random(&initshape, shapenumber);
      figuresshape[count] = initshape;
      balls[counterB] = initshape.shape.ball;
      counterB++;

    } else {
      shapenumber = 1;
      initshape.type = 1;
      init_shape_random(&initshape, shapenumber);
      figuresshape[count] = initshape;
    }
  }
}

struct figure *draw_shape(struct figure *p) {
  if (p->type == 0) {

    DrawCircle(p->shape.ball.posx, p->shape.ball.posy, p->shape.ball.radius,
               p->shape.ball.color);
    globalcountforballs++;
  } else if (p->type == 1) {
    DrawRectangle(p->shape.rectangle.posx, p->shape.rectangle.posy,
                  p->shape.rectangle.radius, p->shape.rectangle.radius,
                  p->shape.rectangle.color);
  }
  return p;
}

struct figure *update_pos(struct figure *p) {
  if (p->type == 1) {
    p->shape.rectangle.posx =
        (WIDTH + p->shape.rectangle.posx + p->shape.rectangle.velx) % WIDTH;
    p->shape.rectangle.posy =
        (HEIGHT + p->shape.rectangle.posy + p->shape.rectangle.vely) % HEIGHT;
  }

  return p;
}

struct figure *update_vel_for_following(struct figure *p) {
  if (p->type == 0) {
  } else if (p->type == 1) {
    int errx = p->shape.rectangle.follows->posx - p->shape.rectangle.posx;
    int erry = p->shape.rectangle.follows->posy - p->shape.rectangle.posy;

    p->shape.rectangle.velx = errx > 0 ? 1 : -1;
    p->shape.rectangle.vely = erry > 0 ? 1 : -1;
  }

  return p;
}

void update_elements() {
  for (size_t i = 0; i < SHAPECOUNT; ++i) {
    draw_shape(update_pos(update_vel_for_following(&figuresshape[i])));
  }
}

int main() {

  srand(time(NULL));
  // return 0;
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);
  init_balls_random();

  while (!WindowShouldClose()) {
    BeginDrawing();
    update_elements();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}