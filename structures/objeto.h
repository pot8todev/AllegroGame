#ifndef OBJETO_H
#define OBJETO_H

#include <allegro5/allegro.h>

typedef struct {
  float L;
  float R;
  float U;
  float D;
} HITBOX;
typedef struct {
  // incremento do movimento
  float dx;
  float dy;
  // modulo do vetor
  float velocidade;
} VEC_VELOCIDADE;

typedef struct {
  ALLEGRO_BITMAP *sprite;
  float posx;
  float posy;
  VEC_VELOCIDADE vec_velocidade;
  int sprite_dir;
  const int sprite_w;
  const int sprite_h;
  const int num_frames;
  const bool colisao;
} OBJETO;

#endif
