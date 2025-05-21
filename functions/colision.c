#include "colision.h"
#include "../structures/objeto.h"
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>

void colision(OBJETO *objeto, OBJETO *personagem, int dir)
{
    // Retângulo do personagem
    float person_posx = personagem->posx, person_posy = personagem->posy;
    float person_w = personagem->sprite_w, person_h = personagem->sprite_h;

    // Retângulo da caixa
    float obj_posx = objeto->posx, obj_posy = objeto->posy;
    float obj_w = objeto->sprite_w, obj_h = objeto->sprite_h - 5;

    // Verifica sobreposição
    if (person_posx < obj_posx + obj_w && person_posx + person_w > obj_posx &&
        person_posy < obj_posy + obj_h && person_posy + person_h > obj_posy)
    {
        // Simples: "empurra" o personagem para fora da caixa dependendo da direção
        if (dir == 0) // baixo
            personagem->posy = obj_posy - person_h;
        else if (dir == 1) // esquerda
            personagem->posx = obj_posx + obj_w;
        else if (dir == 2) // cima
            personagem->posy = obj_posy + obj_h;
        else if (dir == 3) // direita
            personagem->posx = obj_posx - person_w;
    }
}
