#include "allegro5/keycodes.h"
#include "functions/colision.h"
#include "functions/cria_mapa.h"
#include "functions/moving.h"
#include "structures/objeto.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TIPOS_OBJETOS 2
int main() {
  srand(time(NULL));
  al_init();
  al_install_keyboard();
  al_init_image_addon();

  int maxdisplay_w = 640;
  int maxdisplay_h = 640;
  double speed = 1.0 / 40.0;

  char *mapas[] = {"images/fase1.txt", "images/fase2.txt", "images/fase3.txt",
                   "images/fase4.txt", "images/fase5.txt"};
  int num_mapas = sizeof(mapas) / sizeof(mapas[0]);
  mapa *fase_selecionada = vetor_para_lista_circular(mapas, num_mapas);

  bool game_on = true;

  while (game_on) {
    // Inicializações
    ALLEGRO_DISPLAY *disp = al_create_display(maxdisplay_w, maxdisplay_h);
    ALLEGRO_TIMER *timer = al_create_timer(speed);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_BITMAP *sprite = al_load_bitmap("images/sprites.png");
    ALLEGRO_BITMAP *wall = al_load_bitmap("images/wall.png");
    ALLEGRO_BITMAP *floor = al_load_bitmap("images/floor1.png");
    ALLEGRO_BITMAP *lava = al_load_bitmap("images/lava.png");
    ALLEGRO_BITMAP *fruits = al_load_bitmap("images/fruits.png");

    bool keys[ALLEGRO_KEY_MAX] = {0};

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    ALLEGRO_EVENT event;

    // --- Variaveis de jogo ---

    OBJETO objetos[TOTAL_TIPOS_OBJETOS];
    OBJETO personagem = {
        sprite,    {576, 0},               // POSICAO_INICIAL inicio;
        0,         0,         {0, 0, 4.0}, // vec_velocidade
        0,                                 // int sprite_dir;
        TILE_SIZE, TILE_SIZE,
        4,    // const int sprite_w, sprite_h, num_frames;
        true, // const bool colisao;
        true, // visivel
        1     //  quantidade, pode ser incrementada ao longo do codigo
    };
    OBJETO wall_tile = {wall,      {0, 0},    0,  0,    {0, 0, 0}, 0,
                        TILE_SIZE, TILE_SIZE, -0, true, true,      0};

    OBJETO floor_tile = {floor,     {0, 0},    0, 0,    {0, 0, 0}, 0,
                         TILE_SIZE, TILE_SIZE, 0, true, true,      0};

    OBJETO lava_tile = {lava,      {0, 0},    0, 0,    {0, 0, 0}, 0,
                        TILE_SIZE, TILE_SIZE, 0, true, true,      0};
    OBJETO fruits_tile = {fruits,    {0, 0},    0, 0,    {0, 0, 0}, 0,
                          TILE_SIZE, TILE_SIZE, 0, true, true,      0};

    int rand_fruit_tile_x = rand() % 6;
    int rand_fruit_tile_y = rand() % 6;

    // endereço das fases do jogo

    int frame = 0;
    int frame_counter = 0;

    HITBOX *vetorHitbox_wall_tile = NULL;
    HITBOX *vetorHitbox_lava_tile = NULL;
    HITBOX *vetorHitbox_fruits_tile = NULL;

    vetorHitbox_wall_tile =
        inicia_vetorHitbox(fase_selecionada->endereco, &wall_tile, 1);
    vetorHitbox_lava_tile =
        inicia_vetorHitbox(fase_selecionada->endereco, &lava_tile, 2);
    vetorHitbox_fruits_tile =
        inicia_vetorHitbox(fase_selecionada->endereco, &fruits_tile, 4);

    // posiçåo inicial do personagem em cada fase
  int vetorPosInicioPersonagem[][2] = {
      {576, 0}, 
      {100, 20}, 
      {200, 405},
      {200, 405},
      {200, 405}};

    personagem.inicio.pos_init_x =
        vetorPosInicioPersonagem[fase_selecionada->num_fase][0];
    personagem.inicio.pos_init_y =
        vetorPosInicioPersonagem[fase_selecionada->num_fase][1];

    personagem.posx = personagem.inicio.pos_init_x;
    personagem.posy = personagem.inicio.pos_init_y;

    bool fase_on = true;
    bool moving = false;
    // -------------------------

    while (fase_on) {
      al_wait_for_event(queue, &event);

      // Eventos de teclado
      if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        keys[event.keyboard.keycode] = true;

        if (ALLEGRO_KEY_F1 == event.keyboard.keycode) {
          fase_selecionada = fase_selecionada->proxima_fase;
          fase_on = false;
        }

        if (ALLEGRO_KEY_ESCAPE == event.keyboard.keycode) {
          fase_on = false;
          game_on = false;
        }
      } else if (event.type == ALLEGRO_EVENT_KEY_UP)
        keys[event.keyboard.keycode] = false;
      else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        fase_on = false;
        game_on = false;
      }

      // --- Lógica de movimento, direção e animação ---
      if (event.type == ALLEGRO_EVENT_TIMER) {

        personagem.vec_velocidade.dx = 0;
        personagem.vec_velocidade.dy = 0;
        moving = false;

        moving_test_up(keys[ALLEGRO_KEY_UP], &moving, &personagem);
        moving_test_down(keys[ALLEGRO_KEY_DOWN], &moving, &personagem);
        moving_test_right(keys[ALLEGRO_KEY_RIGHT], &moving, &personagem);
        moving_test_left(keys[ALLEGRO_KEY_LEFT], &moving, &personagem);

        limita_mapa(&personagem.posx, &personagem.posy, maxdisplay_w,
                    maxdisplay_h, personagem.sprite_w, personagem.sprite_h);

        // frame loop
        if (moving) {
          // normalizacao vetor diagonal
          normal_vetor(&personagem);

          colision(vetorHitbox_wall_tile, wall_tile.quantidade, &personagem);
          colision_With_Reset(vetorHitbox_lava_tile, lava_tile.quantidade,
                              &personagem);
          colision_Consumable(vetorHitbox_fruits_tile, fruits_tile.quantidade,
                              &personagem, &fruits_tile);

          // aplicaçao do incremento
          if (personagem.vec_velocidade.dx != 0 ||
              personagem.vec_velocidade.dy != 0) {

            personagem.posx += personagem.vec_velocidade.dx;
            personagem.posy += personagem.vec_velocidade.dy;
          }

          // muda frames quando anda
          fps(&frame_counter, &frame, personagem.num_frames);
        }

        else {
          frame = 0; // Parado: usa quadro do meio
        }

        al_clear_to_color(al_map_rgb(255, 255, 255));

        desenha_Objeto(fase_selecionada->endereco, floor_tile, 0, 0, 0);

        desenha_Objeto(fase_selecionada->endereco, wall_tile, 1, 0, 0);
        desenha_Objeto(fase_selecionada->endereco, lava_tile, 2, 0, 0);
        desenha_Objeto(fase_selecionada->endereco, floor_tile, 4, 0, 0);
        // TODO usar um outro parametro
        desenha_Objeto_Consumivel(
            fase_selecionada->endereco, fruits_tile, vetorHitbox_fruits_tile, 4,
            rand_fruit_tile_x * TILE_SIZE, rand_fruit_tile_y * TILE_SIZE);
        al_draw_bitmap_region(sprite, frame * personagem.sprite_w,
                              personagem.sprite_dir * personagem.sprite_h,
                              personagem.sprite_w, personagem.sprite_h,
                              personagem.posx, personagem.posy, 0);

        al_flip_display();
      }
      // ------------------------------------------------
    }

    free(vetorHitbox_lava_tile);
    free(vetorHitbox_wall_tile);
    free(vetorHitbox_fruits_tile);

    // Limpeza

    al_destroy_bitmap(sprite);
    al_destroy_bitmap(wall);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(disp);
    printf("\n%d\n", fase_selecionada->num_fase);
  }
  return 0;
}
