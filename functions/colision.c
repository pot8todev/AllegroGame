#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <time.h>

HITBOX create_hitbox(float x, float y, float w, float h) {
  HITBOX hb;
  hb.L = x;
  hb.R = x + w * 0.6;
  hb.U = y;
  hb.D = y + h * 0.6;
  return hb;
}
#include "colision.h"

void colision(HITBOX *objetos, int num_objetos, OBJETO *personagem,
              bool reset) {
  for (int i = 0; i < num_objetos; i++) {
    int modulo = personagem->vec_velocidade.velocidade;

    HITBOX hitbox_pes_x =
        create_hitbox(personagem->posx + personagem->vec_velocidade.dx,
                      personagem->posy + personagem->sprite_h - PÉS_ALTURA,
                      personagem->sprite_w, PÉS_ALTURA);
    HITBOX hitbox_pes_y =
        create_hitbox(personagem->posx,
                      personagem->posy + personagem->vec_velocidade.dy +
                          personagem->sprite_h - PÉS_ALTURA,
                      personagem->sprite_w, PÉS_ALTURA);

    HITBOX hitbox_obj = objetos[i];

    bool colidiu_x =
        hitbox_pes_x.L < hitbox_obj.R && hitbox_pes_x.R > hitbox_obj.L &&
        hitbox_pes_x.U < hitbox_obj.D && hitbox_pes_x.D > hitbox_obj.U;

    bool colidiu_y =
        hitbox_pes_y.L < hitbox_obj.R && hitbox_pes_y.R > hitbox_obj.L &&
        hitbox_pes_y.U < hitbox_obj.D && hitbox_pes_y.D > hitbox_obj.U;
    if ((colidiu_x || colidiu_y) && reset == true) { // gameOver
      personagem->posx = personagem->inicio.pos_init_x;
      personagem->posy = personagem->inicio.pos_init_y;
      break;
    }
    if (colidiu_x) {
      personagem->vec_velocidade.dx = 0;
      break;
    }
    if (colidiu_y) {
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
