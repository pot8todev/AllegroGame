#pragma once
#include "../structures/objeto.h"
#include <stdbool.h>

void movingTestUp(bool keyTest, bool *moving, OBJETO *obj);
void movingTestDown(bool keyTest, bool *moving, OBJETO *obj);
void movingTestRight(bool keyTest, bool *moving, OBJETO *obj);
void movingTestLeft(bool keyTest, bool *moving, OBJETO *obj);
void fps(int *frame_counter, int *frame, int num_frames);
void normalVetor(float *posY, float *posX, float *posXi, float *posYi);
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h,
                 int sprite_w, int sprite_h);
