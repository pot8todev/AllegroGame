#include "../structures/objeto.h"
#include "colision.h"
#include <stdio.h>
#include <stdlib.h>

// funçao para ajudar alocaçao dinamica de "inicia_vetorHitbox"
int numero_de_objetos(int matriz[LINHAS][COLUNAS], int parametro) {
  int i, j, count = 0;
  for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
      if (matriz[i][j] == parametro) {
        count++; // conta objetos com o valor igual ao parâmetro
      }
    }
  }
  return count;
}

// quero que cada objeto tenha sua HITBOX propia
HITBOX *inicia_vetorHitbox(char mapa[], OBJETO *obj1, int parametroDeBusca) {
  FILE *arquivo;
  int matriz[LINHAS][COLUNAS];
  HITBOX *obj_mapa = NULL;
  int i, j, obj_num = 0;

  arquivo = fopen(mapa, "r");
  if (!arquivo) {
    perror("Erro ao abrir o arquivo");
    return NULL;
  }

  for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
      if (fscanf(arquivo, "%d", &matriz[i][j]) != 1) {
        fclose(arquivo);
        return NULL;
      }
    }
  }
  fclose(arquivo);

  obj1->quantidade = numero_de_objetos(matriz, parametroDeBusca);
  if (obj1->colisao == 1) {
    obj_mapa = malloc(obj1->quantidade * sizeof(HITBOX));
    if (!obj_mapa)
      return NULL;
  }

  for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS; j++) {
      if (matriz[i][j] == parametroDeBusca && obj1->colisao == 1) {
        obj_mapa[obj_num] = create_hitbox(TILE_SIZE * j, TILE_SIZE * i,
                                          TILE_SIZE + 10, TILE_SIZE + 20);
        obj_num++;
      }
    }
  }

  return obj_mapa;
}

void desenha_Objeto(char mapa[], OBJETO obj, int parametroDeBusca) {
  FILE *arquivo;
  int matriz[LINHAS][COLUNAS];

  arquivo = fopen(mapa, "r");

  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      if (fscanf(arquivo, "%d", &matriz[i][j]) != 1) {
        fclose(arquivo);
        return;
      }
    }
  }
  fclose(arquivo);

  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      if (matriz[i][j] == parametroDeBusca) {
        al_draw_bitmap_region(obj.sprite, 0, 0, obj.sprite_w, obj.sprite_h,
                              j * TILE_SIZE, i * TILE_SIZE, 0);
      }
    }
  }
}
