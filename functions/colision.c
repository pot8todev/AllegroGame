#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
HITBOX create_hitbox(float x, float y, float w, float h)
{
  HITBOX hb;
  hb.L = x;
  hb.R = x + w * 0.6;
  hb.U = y;
  hb.D = y + h / 2;
  return hb;
}
#include "colision.h"

void colision(HITBOX *objetos, int num_objetos, OBJETO *personagem)
{
  for (int i = 0; i < num_objetos; i++)
  {
    HITBOX hitbox_personagem = create_hitbox(
        personagem->posx + personagem->vec_velocidade.dx,
        personagem->posy + personagem->vec_velocidade.dy,
        personagem->sprite_w,
        personagem->sprite_h);

    HITBOX hitbox_obj = objetos[i];

    bool colidiu =
        hitbox_personagem.L < hitbox_obj.R &&
        hitbox_personagem.R > hitbox_obj.L &&
        hitbox_personagem.U < hitbox_obj.D &&
        hitbox_personagem.D > hitbox_obj.U;

    if (colidiu)
    {
      personagem->vec_velocidade.dx = 0;
      personagem->vec_velocidade.dy = 0;
      break;
    }
  }
}
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h, int sprite_w, int sprite_h)
{
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
