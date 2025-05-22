#pragma once
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>

void colision(OBJETO *objeto, OBJETO *personagem);
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h,
                 int sprite_w, int sprite_h);
