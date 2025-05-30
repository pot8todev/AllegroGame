#include "moving.h"
#include "../structures/objeto.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void moving_test_up(bool keyTest, bool *moving, OBJETO *obj) {
  if (keyTest) {
    // alterando o incremento
    (obj->vec_velocidade.dy) = -(obj->vec_velocidade.velocidade);
    obj->sprite_dir = 2;
    *moving = true;
  }
}
void moving_test_down(bool keyTest, bool *moving, OBJETO *obj) {
  if (keyTest) {
    obj->vec_velocidade.dy = (obj->vec_velocidade.velocidade);
    obj->sprite_dir = 0;
    *moving = true;
  }
}
void moving_test_right(bool keyTest, bool *moving, OBJETO *obj) {
  if (keyTest) {
    obj->vec_velocidade.dx = (obj->vec_velocidade.velocidade);
    obj->sprite_dir = 3;
    *moving = true;
  }
}
void moving_test_left(bool keyTest, bool *moving, OBJETO *obj) {
  if (keyTest) {
    obj->vec_velocidade.dx = -(obj->vec_velocidade.velocidade);
    obj->sprite_dir = 1;
    *moving = true;
  }
}
void fps(int *frame_counter, int *frame, int num_frames) {
  (*frame_counter)++; // TODO local variable
  if ((*frame_counter) >= 5) {
    *frame = ((*frame) + 1) % num_frames;
    *frame_counter = 0;
  }
}
void normal_vetor(OBJETO *obj) {
  if (obj->vec_velocidade.dx && obj->vec_velocidade.dy) {
    obj->vec_velocidade.dy /= sqrt(2);
    obj->vec_velocidade.dx /= sqrt(2);
  }
}
