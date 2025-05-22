#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>

void colision(OBJETO *objeto, OBJETO *personagem) {
  // Retângulo do personagem
  float person_posx = personagem->posx, person_posy = personagem->posy;
  float person_w = personagem->sprite_w, person_h = personagem->sprite_h;

  // Retângulo da caixa
  float obj_posx = objeto->posx, obj_posy = objeto->posy;
  float obj_w = objeto->sprite_w, obj_h = objeto->sprite_h - 5;

  // Verifica sobreposição
  if (person_posx < obj_posx + obj_w && person_posx + person_w > obj_posx &&
      person_posy < obj_posy + obj_h && person_posy + person_h > obj_posy) {
    // Simples: "empurra" o personagem para fora da caixa dependendo da direção
    if (personagem->sprite_dir == 0) // baixo
      personagem->posy = obj_posy - person_h;
    else if (personagem->sprite_dir == 1) // esquerda
      personagem->posx = obj_posx + obj_w;
    else if (personagem->sprite_dir == 2) // cima
      personagem->posy = obj_posy + obj_h;
    else if (personagem->sprite_dir == 3) // direita
      personagem->posx = obj_posx - person_w;
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
