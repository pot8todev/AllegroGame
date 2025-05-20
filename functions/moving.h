#pragma once

void movingTestUp(bool control, bool *moving, float speed, int *spriteDir, float *pos);
void movingTestDown(bool control, bool *moving, float speed, int *spriteDir, float *pos);
void movingTestRight(bool control, bool *moving, float speed, int *spriteDir, float *pos);
void movingTestLeft(bool control, bool *moving, float speed, int *spriteDir, float *pos);
void fps(int *frame_counter, int* frame, int num_frames);
void normalVetor(float *posY, float *posX, float* posXi, float* posYi);
void limita_mapa(float *posx, float *posy, int maxdisplay_w, int maxdisplay_h, int sprite_w, int sprite_h);