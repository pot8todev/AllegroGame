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

#define TOTAL_TIPOS_OBJETOS 2
int main() {
  al_init();
  al_install_keyboard();
  al_init_image_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_primitives_addon();

  int maxdisplay_w = 640;
  int maxdisplay_h = 640;
  double speed = 1.0 / 40.0;

  ALLEGRO_DISPLAY *disp = al_create_display(maxdisplay_w, maxdisplay_h);
  ALLEGRO_TIMER *timer = al_create_timer(speed); // TODO deixar mais generico
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_BITMAP *sprite = al_load_bitmap("images/sprites.png");
  ALLEGRO_BITMAP *wall = al_load_bitmap("images/wall.png");
  ALLEGRO_BITMAP *floor = al_load_bitmap("images/floor1.png");
  ALLEGRO_BITMAP *lava = al_load_bitmap("images/lava.png");

  bool keys[ALLEGRO_KEY_MAX] = {0};

  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_keyboard_event_source());

  al_start_timer(timer);

  ALLEGRO_EVENT event;

  // --- Variaveis de jogo ---

  OBJETO objetos[TOTAL_TIPOS_OBJETOS];
  OBJETO personagem = {
      sprite,   // ALLEGRO_BITMAP *sprite;
      {576, 0}, // POSICAO_INICIAL inicio;
      576,
      0,           // float posx, float posy;
      {0, 0, 4.0}, // vec_velocidade vec_velocidade;
      0,           // int sprite_dir;
      TILE_SIZE,
      TILE_SIZE,
      4,    // const int sprite_w, sprite_h, num_frames;
      true, // const bool colisao;
      1     // int quantidade;
  };
  OBJETO wall_tile = {wall,      {0, 0},    0,  0,    {0, 0, 0}, 0,
                      TILE_SIZE, TILE_SIZE, -0, true, 0};

  OBJETO floor_tile = {floor,     {0, 0},    0, 0,    {0, 0, 0}, 0,
                       TILE_SIZE, TILE_SIZE, 0, true, 0};

  OBJETO lava_tile = {lava,      {0, 0},    0, 0,    {0, 0, 0}, 0,
                      TILE_SIZE, TILE_SIZE, 0, true, 0};
  personagem.inicio.pos_init_x = 576;
  personagem.inicio.pos_init_y = 0;

  personagem.posx = personagem.inicio.pos_init_x;
  personagem.posy = personagem.inicio.pos_init_y;
  int frame = 0;
  int frame_counter = 0;
  HITBOX *vetorHitbox_wall_tile =
      inicia_vetorHitbox("images/dados.txt", &wall_tile, 1);
  HITBOX *vetorHitbox_lava_tile =
      inicia_vetorHitbox("images/dados.txt", &lava_tile, 2);
  bool its_on = true;
  bool moving = false;

  // -------------------------

  while (its_on) {
    al_wait_for_event(queue, &event);

    // Eventos de teclado
    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
      keys[event.keyboard.keycode] = true;
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
      keys[event.keyboard.keycode] = false;
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      its_on = false;

    // --- Lógica de movimento, direção e animação ---
    if (event.type == ALLEGRO_EVENT_TIMER) {

      personagem.vec_velocidade.dx = 0;
      personagem.vec_velocidade.dy = 0;
      moving = false;

      moving_test_up(keys[ALLEGRO_KEY_UP], &moving, &personagem);
      moving_test_down(keys[ALLEGRO_KEY_DOWN], &moving, &personagem);
      moving_test_right(keys[ALLEGRO_KEY_RIGHT], &moving, &personagem);
      moving_test_left(keys[ALLEGRO_KEY_LEFT], &moving, &personagem);

      moving_test_up(keys[ALLEGRO_KEY_W], &moving, &personagem);
      moving_test_down(keys[ALLEGRO_KEY_S], &moving, &personagem);
      moving_test_right(keys[ALLEGRO_KEY_D], &moving, &personagem);
      moving_test_left(keys[ALLEGRO_KEY_A], &moving, &personagem);

      limita_mapa(&personagem.posx, &personagem.posy, maxdisplay_w,
                  maxdisplay_h, personagem.sprite_w, personagem.sprite_h);

      // frame loop
      if (moving) {
        // aplicaçao do incremento
        normal_vetor(&personagem);
        colision(vetorHitbox_wall_tile, wall_tile.quantidade, &personagem,
                 false);
        colision(vetorHitbox_lava_tile, lava_tile.quantidade, &personagem,
                 true);
        personagem.posx += personagem.vec_velocidade.dx;
        personagem.posy += personagem.vec_velocidade.dy;
        // normalizacao vetor diagonal

        // muda frames quando anda
        fps(&frame_counter, &frame, personagem.num_frames);
      } else {
        frame = 0; // Parado: usa quadro do meio
      }
      al_clear_to_color(al_map_rgb(255, 255, 255));

      desenha_Objeto("images/dados.txt", floor_tile, 0);
      // draw_floor("images/dados.txt", floor_tile);
      desenha_Objeto("images/dados.txt", wall_tile, 1);
      desenha_Objeto("images/dados.txt", lava_tile, 2);
      al_draw_bitmap_region(sprite, frame * personagem.sprite_w,
                            personagem.sprite_dir * personagem.sprite_h,
                            personagem.sprite_w, personagem.sprite_h,
                            personagem.posx, personagem.posy, 0);

      al_flip_display();
    }
    // ------------------------------------------------
  }

  // Limpeza
  al_destroy_bitmap(sprite);
  al_destroy_bitmap(wall);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  al_destroy_display(disp);
  return 0;
}
