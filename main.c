#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_ttf.h>
#include "moving.h"

int main()
{
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    int maxdisplay_w = 800;
    int maxdisplay_h = 600;

    ALLEGRO_DISPLAY *disp = al_create_display(maxdisplay_w, maxdisplay_h);
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_BITMAP *sprite = al_load_bitmap("sprites.png");

    // --- Adicione estas constantes e variáveis ---
    const int SPRITE_W = 32;
    const int SPRITE_H = 32;
    const int NUM_FRAMES = 4;
    int dir = 0; // 0 = baixo, 1 = esquerda, 2 = cima, 3 = direita
    int frame = 0;
    int frame_counter = 0;
    float x = 600, y = 100;
    float speed = 2.0;
    bool keys[ALLEGRO_KEY_MAX] = {0};
    // --------------------------------------------

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    bool running = true;
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
            bool moving = false;
           
            movingTest(keys[ALLEGRO_KEY_UP], &moving, speed, &dir, &y);

            if (keys[ALLEGRO_KEY_LEFT])
            {
                x -= speed;
                dir = 1;
                moving = true;
            }
            if (keys[ALLEGRO_KEY_DOWN])
            {
                y += speed;
                dir = 0;
                moving = true;
            }
            if (keys[ALLEGRO_KEY_RIGHT])
            {
                x += speed;
                dir = 3;
                moving = true;
            }

            if (moving)
            {
                frame_counter++;
                if (frame_counter >= 10)
                {
                    frame = (frame + 1) % NUM_FRAMES;
                    frame_counter = 0;
                }
            }
            else // Gravidade
            {

                if (x < 0 || y < 0)
                {
                    continue;
                }

                y -= speed / 2;
                frame = 0; // Parado: usa quadro do meio
            }
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap_region(sprite, frame * SPRITE_W, dir * SPRITE_H, SPRITE_W, SPRITE_H, x, y, 0);
            al_flip_display();
        }
        // ------------------------------------------------
    }

    // Limpeza
    al_destroy_bitmap(sprite);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(disp);
    return 0;
}
