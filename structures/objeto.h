#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <allegro5/allegro_image.h>

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

/*TODO
  OBJETO personagem = {al_load_bitmap("images/sprites.png"), 300, 200, 4.0, 32, 32, 4};
     OBJETO woodenCrateBox = {woodenCrate, 60, 60, 0, 32, 32, 0};
*/

#endif