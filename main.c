#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_ttf.h>
#include "functions/moving.h"
#include "functions/colision.h"
#include "structures/objeto.h"
#include <stdio.h>
int main()
{
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    //--- Variáveis do jogo ---

    int maxdisplay_w = 600;
    int maxdisplay_h = 400;

    bool moving = false;

    // -----------------------

    ALLEGRO_DISPLAY *disp = al_create_display(maxdisplay_w, maxdisplay_h);
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0); // TODO deixar mais generico
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_BITMAP *sprite = al_load_bitmap("images/sprites.png");
    ALLEGRO_BITMAP *woodenCrate = al_load_bitmap("images/woodenCrate.png");

    // --- Variaveis de jogo ---
    OBJETO personagem = {al_load_bitmap("images/sprites.png"), 300, 200, 4.0, 32, 32, 4};
    OBJETO woodenCrateBox = {woodenCrate, 60, 60, 0, 32, 32, 0};

    float posxi, posyi;

    int dir = 0; // 0 = baixo, 1 = esquerda, 2 = cima, 3 = direita
    int frame = 0;
    int frame_counter = 0;
    bool running = true;

    // -------------------------

    bool keys[ALLEGRO_KEY_MAX] = {0};

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    ALLEGRO_EVENT event;

    while (running)
    {
        al_wait_for_event(queue, &event);

        // Eventos de teclado
        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            keys[event.keyboard.keycode] = true;
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
            keys[event.keyboard.keycode] = false;
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            running = false;

        // --- Lógica de movimento, direção e animação ---

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            moving = false;

            posxi = personagem.posx;
            posyi = personagem.posy;

            movingTestUp(keys[ALLEGRO_KEY_UP], &moving, personagem.velocidade, &dir, &personagem.posy);
            movingTestDown(keys[ALLEGRO_KEY_DOWN], &moving, personagem.velocidade, &dir, &personagem.posy);
            movingTestRight(keys[ALLEGRO_KEY_RIGHT], &moving, personagem.velocidade, &dir, &personagem.posx);
            movingTestLeft(keys[ALLEGRO_KEY_LEFT], &moving, personagem.velocidade, &dir, &personagem.posx);

            // Limita o personagem dentro da tela
            if (personagem.posx < 0)
                personagem.posx = 0;
            if (personagem.posx > (maxdisplay_w - personagem.sprite_w))
                personagem.posx = (maxdisplay_w - personagem.sprite_w);
            if (personagem.posy < 0)
                personagem.posy = 0;
            if (personagem.posy > (maxdisplay_h - personagem.sprite_h))
                personagem.posy = (maxdisplay_h - personagem.sprite_h);

            // frame loop
            if (moving)
            {

                if (personagem.posy != posyi && personagem.posx != posxi)
                {
                    float dy = (personagem.posy - posyi);
                    float dx = (personagem.posx - posxi);
                    dy /= (1.4); // TODO math.h
                    dx /= (1.4);
                    personagem.posy = posyi + dy;
                    personagem.posx = posxi + dx;
                }

                frame_counter++;
                if (frame_counter >= 10)
                {
                    frame = (frame + 1) % personagem.num_frames;
                    frame_counter = 0;
                }
                posxi = personagem.posx;
                posyi = personagem.posy;
            }
            else
            {
                frame = 0; // Parado: usa quadro do meio
            }
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap_region(sprite, frame * personagem.sprite_w, dir * personagem.sprite_h, personagem.sprite_w, personagem.sprite_h, personagem.posx, personagem.posy, 0);

            al_draw_bitmap_region(woodenCrateBox.sprite, 0, 0, woodenCrateBox.sprite_w, woodenCrateBox.sprite_h, woodenCrateBox.posx, woodenCrateBox.posy, 0);

            al_flip_display();
        }
        // ------------------------------------------------
    }

    // Limpeza
    al_destroy_bitmap(sprite);
    al_destroy_bitmap(woodenCrate);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(disp);
    return 0;
}
