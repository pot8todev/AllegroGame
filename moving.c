#include <stdbool.h>
#include "moving.h"

void movingTestUp(bool control, bool *moving, float speed, int *spriteDir, float *pos)
{
    if (control)
    {  
        *pos-= speed;
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
