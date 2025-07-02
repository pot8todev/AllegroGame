#include "../structures/objeto.h"
#include <stdio.h>
#include <stdlib.h>

HITBOX *inicia_vetorHitbox(char mapa[], OBJETO *obj1, int parametroDeBusca);

void desenha_Objeto(char mapa[], OBJETO obj, int parametroDeBusca, float sx,
                    float sy);
void desenha_Objeto_Consumivel(char mapa[], OBJETO obj, HITBOX *hitbox,
                               int parametroDeBusca, float sx, float s);

mapa *cria_no(char endereco[50], int num_fase, mapa *proxima_fase);
mapa *vetor_para_lista_circular(char *vetor_mapas[], int size);
