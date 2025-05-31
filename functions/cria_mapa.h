#include "../structures/objeto.h"
#include <stdio.h>
#include <stdlib.h>

HITBOX *inicia_vetorHitbox(char mapa[], OBJETO *obj1, int parametroDeBusca);

void desenha_Objeto(char mapa[], OBJETO obj, int parametroDeBusca, float sx,
                    float sy);
