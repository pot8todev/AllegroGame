#include <stdbool.h>
#include "moving.h"

void movingTestUp(bool control, bool *moving, float speed, int *spriteDir, float *pos)
{
    if (control)
    {
        *pos -= speed;
        *spriteDir = 2;
        *moving = true;
    }
}
void movingTestDown(bool control, bool *moving, float speed, int *spriteDir, float *pos)
{
    if (control)
    {
        *pos += speed;
        *spriteDir = 0;
        *moving = true;
    }
}
void movingTestRight(bool control, bool *moving, float speed, int *spriteDir, float *pos)
{
    if (control)
    {
        *pos += speed;
        *spriteDir = 3;
        *moving = true;
    }
}
void movingTestLeft(bool control, bool *moving, float speed, int *spriteDir, float *pos)
{
    if (control)
    {
        *pos -= speed;
        *spriteDir = 1;
        *moving = true;
    }
}
void fps(int *frame_counter, int *frame, int num_frames)
{
    *frame_counter++; // TODO local variable
    if (*frame_counter >= 10)
    {
        *frame = (*frame + 1) % num_frames;
        *frame_counter = 0;
    }
}
void normalVetor(float *posY, float *posX, float* posXi, float* posYi)
{
     if (*posY != *posYi && *posX != *posXi)
                {
                    float dy = (*posY - *posYi);
                    float dx = (*posX - *posXi);
                    dy /= (1.4); // TODO math.h
                    dx /= (1.4);
                    *posY = *posYi + dy;
                    *posX = *posXi + dx;
                }
            }