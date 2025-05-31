#pragma once
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>

void colision(HITBOX *objetosHITBOX, int num_objetos, OBJETO *personagem);

void colision_With_Reset(HITBOX *objetos, int num_objetos, OBJETO *personagem);

void colision_Consumable(HITBOX *objetos, int num_objetos, OBJETO *personagem,
                         OBJETO *objeto);
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h,
                 int sprite_w, int sprite_h);
HITBOX create_hitbox(float x, float y, float w, float h);
