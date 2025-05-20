#include <stdbool.h>
#include "colision.h"

void colision(float *x1, float *y1, float *x2, float *y2, int w1, int h1, int w2, int h2)
{
    if (*x1 < *x2)
        *x1 = *x2 + w2;
    if (*x1 > *x2)
        *x1 = *x2 - w2;
    if (*y1 < *y2)
        *y1 = *y2 + h2;
    if (*y1 > *y2)
        *y1 = *y2 - h2;
}