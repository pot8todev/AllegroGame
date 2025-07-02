#include <allegro5/allegro.h>
#ifndef OBJETO_H
#define OBJETO_H

#define LINHAS 20
#define COLUNAS 20
#define TILE_SIZE 32

#define PÉS_ALTURA 12 // altura da hitbox dos pés (ajuste conforme necessário)

typedef struct mapa {
  char endereco[50];
  int num_fase; // numero da fase
  struct mapa *proxima_fase;

} mapa;
typedef struct {
  float L;
  float R;
  float U;
  float D;
} HITBOX;

typedef struct {
  // incremento do movimento
  float dx;
  float dy;
  // modulo do vetor
  float velocidade;
} vec_velocidade;

typedef struct {
  // posiçao inicial do jogo
  float pos_init_x;
  float pos_init_y;
} POSICAO_INICIAL;

typedef struct {
  ALLEGRO_BITMAP *sprite;
  POSICAO_INICIAL inicio;
  float posx;
  float posy;
  vec_velocidade vec_velocidade;
  int sprite_dir;
  const int sprite_w;
  const int sprite_h;
  const int num_frames;
  const bool colisao;
  bool visivel;
  int quantidade;
} OBJETO;

#endif
