#include <stdio.h>
#include <stdlib.h>
#include "../structures/objeto.h"

#define LINHAS 20
#define COLUNAS 20

void cria_mapa(char mapa[], OBJETO obj1)
{
    FILE *arquivo;
    int matriz[LINHAS][COLUNAS];
    int i, j;

    arquivo = fopen(mapa, "r");

    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            if (fscanf(arquivo, "%d", &matriz[j][i]) != 1)
            {
                fclose(arquivo);
                return;
            }
        }
    }

    fclose(arquivo);

    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            if (matriz[j][i] == 1)
            {
                al_draw_bitmap_region(obj1.sprite, 0, 0, obj1.sprite_w, obj1.sprite_h, (j * 32), (i * 32), 0);
            }
        }
    }
}
