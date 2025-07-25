#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

HITBOX create_hitbox(float x, float y, float w, float h) {
  HITBOX hb;
  hb.L = x;
  hb.R = x + w * 0.6;
  hb.U = y;
  hb.D = y + h * 0.6;
  return hb;
}

HITBOX create_hitbox_scaled(float x, float y, float w, float h, float scale) {
  HITBOX hb;
  float scaled_w = w * scale;
  float scaled_h = h * scale;
  hb.L = x;
  hb.R = x + scaled_w;
  hb.U = y;
  hb.D = y + scaled_h;
  return hb;
}

// Calcula a hitbox dos pés com deslocamento X
HITBOX get_hitbox_pes_x(const OBJETO *p) {
  return create_hitbox(p->posx + p->vec_velocidade.dx,
                       p->posy + (p->sprite_h - PÉS_ALTURA), p->sprite_w,
                       PÉS_ALTURA);
}

// Calcula a hitbox dos pés com deslocamento Y
HITBOX get_hitbox_pes_y(const OBJETO *p) {
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
  HITBOX hitbox_pes_y = get_hitbox_pes_y(personagem);

  for (int i = 0; i < num_objetos; i++) {

    HITBOX hitbox_obj = objetosHITBOX[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);

    if (colidiu_x) {
      personagem->vec_velocidade.dx = 0;
    }
    if (colidiu_y) {
      personagem->vec_velocidade.dy = 0;
    }
  }
}

void colision_With_Reset(HITBOX *objetos, int num_objetos, OBJETO *personagem) {
  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = get_hitbox_pes_y(personagem);

  for (int i = 0; i < num_objetos; i++) {

    HITBOX hitbox_obj = objetos[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);
    if ((colidiu_x || colidiu_y)) { // gameOver
      personagem->colisao = false;

      break;
    }
  }
}

void colision_Consumable(HITBOX *objetos, int num_objetos, OBJETO *personagem,
                         OBJETO *objeto) {

  HITBOX hitbox_pes_x = get_hitbox_pes_x(personagem);
  HITBOX hitbox_pes_y = get_hitbox_pes_y(personagem);

  for (int i = 0; i < num_objetos; i++) {
    HITBOX hitbox_obj = objetos[i];

    bool colidiu_x = testa_colisao(hitbox_pes_x, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_pes_y, hitbox_obj);
    if ((colidiu_x || colidiu_y)) { // gameOver
      printf("coletado\n");

      // "remove" o objeto
      objetos[i] = (HITBOX){0, 0, 0, 0};

      return;
    }
  }
  return;
}
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h,
                 int sprite_w, int sprite_h) {
  const int margin = 12;

  // Horizontal
  if (*posx < -sprite_w + margin)
    *posx = maxdisplay_w - margin;
  else if (*posx > maxdisplay_w - margin)
    *posx = -sprite_w + margin;

  // Vertical
  if (*posy < -sprite_h + margin)
    *posy = maxdisplay_h - margin;
  else if (*posy > maxdisplay_h - margin)
    *posy = -sprite_h + margin;
}

void colision_enemy_scenery(HITBOX *objetosHITBOX, int num_objetos,
                            OBJETO *lava_enemy, int maxdisplay_w,
                            int maxdisplay_h) {

  HITBOX hitbox_lava_enemy =
      create_hitbox_scaled(lava_enemy->posx, lava_enemy->posy,
                           lava_enemy->sprite_w, lava_enemy->sprite_h, 1.0);

  for (int i = 0; i < num_objetos; i++) {
    HITBOX hitbox_obj = objetosHITBOX[i];

    bool colidiu_x = testa_colisao(hitbox_lava_enemy, hitbox_obj);
    bool colidiu_y = testa_colisao(hitbox_lava_enemy, hitbox_obj);

    if (colidiu_x) {
      lava_enemy->vec_velocidade.dx *= -1;
    }
    if (colidiu_y) {
      lava_enemy->vec_velocidade.dy *= -1;
    }
  }

  // 🔽 Limita posição do inimigo ao tamanho da tela
  limita_mapa(&(lava_enemy->posx), &(lava_enemy->posy), maxdisplay_w,
              maxdisplay_h, lava_enemy->sprite_w, lava_enemy->sprite_h);
}

void colision_With_Enemy(OBJETO *lava_enemy, OBJETO *personagem) {
  HITBOX hitbox_lava_enemy =
      create_hitbox_scaled(lava_enemy->posx, lava_enemy->posy,
                           lava_enemy->sprite_w, lava_enemy->sprite_h, 1.0);
  HITBOX hitbox_personagem =
      create_hitbox_scaled(personagem->posx, personagem->posy,
                           personagem->sprite_w, personagem->sprite_h, 1.0);

  bool test = testa_colisao(hitbox_personagem, hitbox_lava_enemy);
  if (test) { // gameOver
    personagem->colisao = false;
  }
}
