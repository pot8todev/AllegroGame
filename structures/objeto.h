#ifndef OBJETO_H
#define OBJETO_H

#include <allegro5/allegro.h>

typedef struct
{
  ALLEGRO_BITMAP *sprite;
  float posx;
  float posy;
  float velocidade;
  const int sprite_w;
  const int sprite_h;
  const int num_frames;
} OBJETO;

#endif