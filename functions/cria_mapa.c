#include <stdio.h>
#include <stdlib.h>

#define LINHAS 20
#define COLUNAS 20

void cria_mapa(char mapa[])
{
    FILE *arquivo;
    int matriz[LINHAS][COLUNAS];
    int i, j;

    arquivo = fopen(mapa, "r");

    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            if (fscanf(arquivo, "%d", &matriz[i][j]) != 1)
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
            if (matriz[i][j] == 1)
            {
                al_draw_bitmap_region(wooden_crate_box.sprite, 0, 0, wooden_crate_box.sprite_w, wooden_crate_box.sprite_h, wooden_crate_box.posx, wooden_crate_box.posy, 0);
            }
        }
    }
}
