#include <stdbool.h>
#include "moving.h"

void movingTest(bool control, bool *moving, float speed, int *spriteDir, float *y, float *x)
{
    if (control)
    {  
        *y -= speed;
        *spriteDir = 2;
        *moving = true;
    }
}