#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
HITBOX create_hitbox(float x, float y, float w, float h) {
  HITBOX hb;
  hb.L = x;
  hb.R = x + w*0.6;
  hb.U = y;
  hb.D = y + h/2;
  return hb;
}
void colision(OBJETO *objeto, OBJETO *personagem) {
    // Cria hitboxes futuras considerando o movimento
    HITBOX hitbox_personagem = create_hitbox(
            //posiçao do personagem pos deslocamento
        personagem->posx + personagem->vecVelocidade.dx,
        personagem->posy + personagem->vecVelocidade.dy,
        personagem->sprite_w,
        personagem->sprite_h
    );

    HITBOX hitbox_objeto = create_hitbox(
        objeto->posx,
        objeto->posy,
        objeto->sprite_w,
        objeto->sprite_h
    );

    // Verifica colisão AABB (Axis-Aligned Bounding Box)
    bool colidiu =
        hitbox_personagem.L < hitbox_objeto.R &&
        hitbox_personagem.R > hitbox_objeto.L &&
        hitbox_personagem.U < hitbox_objeto.D &&
        hitbox_personagem.D > hitbox_objeto.U;

    if (colidiu) {
        personagem->vecVelocidade.dx = 0;
        personagem->vecVelocidade.dy = 0;
    }
}void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h,
                 int sprite_w, int sprite_h) {
  // Limita o personagem dentro da tela
  if (*posx < 0)
    *posx = 0;
  if (*posx > (maxdisplay_w - sprite_w))
    *posx = (maxdisplay_w - sprite_w);
  if (*posy < 0)
    *posy = 0;
  if (*posy > (maxdisplay_h - sprite_h))
    *posy = (maxdisplay_h - sprite_h);
}
