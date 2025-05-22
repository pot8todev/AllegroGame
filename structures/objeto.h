#ifndef OBJETO_H
#define OBJETO_H

#include <allegro5/allegro.h>
typedef struct {
  // incremento do movimento
  float dx;
  float dy;
  // modulo do vetor
  float velocidade;
} vec_velocidade;

typedef struct {
  ALLEGRO_BITMAP *sprite;
  float posx;
  float posy;
  vec_velocidade vecVelocidade;
  int sprite_dir;
  const int sprite_w;
  const int sprite_h;
  const int num_frames;
} OBJETO;

#endif
