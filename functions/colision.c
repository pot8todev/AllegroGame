#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#define PÉS_ALTURA 12 // altura da hitbox dos pés (ajuste conforme necessário)
HITBOX create_hitbox(float x, float y, float w, float h) {
  HITBOX hb;
  hb.L = x;
  hb.R = x + w * 0.6;
  hb.U = y;
  hb.D = y + h * 0.6;
  return hb;
}
#include "colision.h"

void colision(HITBOX *objetos, int num_objetos, OBJETO *personagem) {
  for (int i = 0; i < num_objetos; i++) {
    int modulo = personagem->vec_velocidade.velocidade;

    HITBOX hitbox_pes =
        create_hitbox(personagem->posx + personagem->vec_velocidade.dx,
                      personagem->posy + personagem->vec_velocidade.dy +
                          personagem->sprite_h - PÉS_ALTURA,
                      personagem->sprite_w, PÉS_ALTURA);

    HITBOX hitbox_obj = objetos[i];

    bool colidiu = hitbox_pes.L < hitbox_obj.R && hitbox_pes.R > hitbox_obj.L &&
                   hitbox_pes.U < hitbox_obj.D && hitbox_pes.D > hitbox_obj.U;

    if (colidiu) {
      personagem->vec_velocidade.dx = 0;
      personagem->vec_velocidade.dy = 0;
      break;
    }
  }
}
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h,
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
