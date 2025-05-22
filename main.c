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
    #include <stdio.h>

    int main()
    {
        al_init();
        al_install_keyboard();
        al_init_image_addon();
        al_init_font_addon();
        al_init_ttf_addon();
        al_init_primitives_addon();

        int maxdisplay_w = 640;
        int maxdisplay_h = 640;

        ALLEGRO_DISPLAY *disp = al_create_display(maxdisplay_w, maxdisplay_h);
        ALLEGRO_TIMER *timer =
            al_create_timer(1.0 / 60.0); // TODO deixar mais generico
        ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
        ALLEGRO_BITMAP *sprite = al_load_bitmap("images/sprites.png");
        ALLEGRO_BITMAP *wooden_crate = al_load_bitmap("images/wooden_crate.png");

        bool keys[ALLEGRO_KEY_MAX] = {0};

        al_register_event_source(queue, al_get_display_event_source(disp));
        al_register_event_source(queue, al_get_timer_event_source(timer));
        al_register_event_source(queue, al_get_keyboard_event_source());

        al_start_timer(timer);

        ALLEGRO_EVENT event;

        // --- Variaveis de jogo ---

        OBJETO personagem = {sprite, 300, 200, {0, 0, 4.0}, 0, 32, 32, 4};
        OBJETO wooden_crate_box = {wooden_crate, 60, 60, {0, 0, 0}, 0, 32, 32, 0};

        float posxi, posyi;

        // int dir = 0; // 0 = baixo, 1 = esquerda, 2 = cima, 3 = direita
        int frame = 0;
        int frame_counter = 0;

        bool running = true;
        bool moving = false;

        // -------------------------

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
                if (moving)
                {
                    // aplicaçao do incremento
                    normal_vetor(&personagem);
                    personagem.posx += personagem.vec_velocidade.dx;
                    personagem.posy += personagem.vec_velocidade.dy;
                    // normalizacao vetor diagonal

                    // TODO fps func
                    frame_counter++;
                    if (frame_counter >= 10)
                    {
                        frame = (frame + 1) % personagem.num_frames;
                        frame_counter = 0;
                    }

                    colision(&wooden_crate_box, &personagem);
                }
                else
                {
                    frame = 0; // Parado: usa quadro do meio
                }
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap_region(wooden_crate_box.sprite, 0, 0,
                                    wooden_crate_box.sprite_w,
                                    wooden_crate_box.sprite_h, wooden_crate_box.posx,
                                    wooden_crate_box.posy, 0);
                cria_mapa("images/dados.txt", wooden_crate_box);
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
        al_destroy_bitmap(wooden_crate);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
        al_destroy_display(disp);
        return 0;
    }
