#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>

void colision(OBJETO *objeto, OBJETO *personagem)
{
    float colision_area_Rx = (objeto->posx + (objeto->sprite_w) / 2);
    float colision_area_Lx = (objeto->posx - (objeto->sprite_w) / 2);
    float colision_area_Ty = (objeto->posy + (objeto->sprite_h) / 2);
    float colision_area_By = (objeto->posy - (objeto->sprite_h) / 2);

    bool vertical_interval = (personagem->posy < colision_area_Ty || personagem->posy > colision_area_By);
    bool horizontal_interval = (personagem->posx < colision_area_Rx || personagem->posx > colision_area_Lx);

    if (((personagem->posx) < colision_area_Rx) && vertical_interval)
    {
        personagem->posx = colision_area_Rx + personagem->sprite_w;
    }
    if (personagem->posx > colision_area_Lx && vertical_interval)
    {
        personagem->posx = colision_area_Lx;
    }

    if (personagem->posy < colision_area_Ty && horizontal_interval)
    {
        personagem->posy = colision_area_Ty;
    }
    if (personagem->posy > colision_area_By && horizontal_interval)
    {
        personagem->posy = colision_area_By;
    }
}
