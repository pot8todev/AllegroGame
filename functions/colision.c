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
} // Calcula a hitbox dos pés com deslocamento X
HITBOX get_hitbox_pes_x(const OBJETO *p) {
  return create_hitbox(p->posx + p->vec_velocidade.dx,
                       p->posy + (p->sprite_h - PÉS_ALTURA), p->sprite_w,
                       PÉS_ALTURA);
}

// Calcula a hitbox dos pés com deslocamento Y
HITBOX geto_hitbox_pes_y(const OBJETO *p) {
  return create_hitbox(
      p->posx, p->posy + p->vec_velocidade.dy + (p->sprite_h - PÉS_ALTURA),
      p->sprite_w, PÉS_ALTURA);
}

bool testa_colisao(HITBOX a, HITBOX b) {
  return a.L < b.R && a.R > b.L && a.U < b.D && a.D > b.U;
}

/*
 * 1)pega a hitbox dos pes do personagem-
 * 2)supoe que o incremento foi adicionado
 * 3)olha todos os elementos do vetor hitbox e ve se houve a sobreposiçao
 * da hitbox_pes_personagem com hitbox_obj
 */
void colision(HITBOX *objetosHITBOX, int num_objetos, OBJETO *personagem) {
  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = geto_hitbox_pes_y(personagem);
  for (int i = 0; i < num_objetos; i++) {

    HITBOX hitbox_obj = objetosHITBOX[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);

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

void colision_With_Reset(HITBOX *objetos, int num_objetos, OBJETO *personagem) {
  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = geto_hitbox_pes_y(personagem);
  for (int i = 0; i < num_objetos; i++) {

    HITBOX hitbox_obj = objetos[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);
    if ((colidiu_x || colidiu_y)) { // gameOver
      personagem->posx = personagem->inicio.pos_init_x;
      personagem->posy = personagem->inicio.pos_init_y;
      break;
    }
  }
}
void colision_Consumable(HITBOX *objetos, int num_objetos, OBJETO *personagem) {

  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = geto_hitbox_pes_y(personagem);

  for (int i = 0; i < num_objetos; i++) {
    HITBOX hitbox_obj = objetos[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);
    if ((colidiu_x || colidiu_y)) { // gameOver
      personagem->posx = personagem->inicio.pos_init_x;
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
