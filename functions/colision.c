#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>

bool colidiu(OBJETO *objeto, OBJETO *personagem) {}
void colision(OBJETO *objeto, OBJETO *personagem) {
  // norma do vetor de movimento

  // Retângulo do personagem
  float person_posx = personagem->posx, person_posy = personagem->posy;
  float person_nova_posx = personagem->posx + personagem->vec_velocidade.dx;
  float person_nova_posy = personagem->posy + personagem->vec_velocidade.dy;

  float person_w = personagem->sprite_w, person_h = personagem->sprite_h;

  // Retângulo da caixa
  float obj_posx = objeto->posx, obj_posy = objeto->posy;
  float obj_w = objeto->sprite_w + 10, obj_h = objeto->sprite_h + 10;

  // SE o movimento acontecesse e causasse uma colisao:
  bool colidiux = person_nova_posy < obj_posy + obj_h / 2 &&
                  person_nova_posy + person_h / 2 > obj_posy &&
                  person_nova_posx < obj_posx + obj_w / 2 &&
                  person_nova_posx + (person_w / 2) + 5 > obj_posx;
  if (colidiux) {
    // Inverte o vetor de movimento
    personagem->vec_velocidade.dx = 0;
    personagem->vec_velocidade.dy = 0;
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
