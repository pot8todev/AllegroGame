#pragma once
#include "../structures/objeto.h"
#include <stdbool.h>

void movingTestUp(bool keyTest, bool *moving, OBJETO *obj);
void movingTestDown(bool keyTest, bool *moving, OBJETO *obj);
void movingTestRight(bool keyTest, bool *moving, OBJETO *obj);
void movingTestLeft(bool keyTest, bool *moving, OBJETO *obj);
void fps(int *frame_counter, int *frame, int num_frames);
void normalVetor(OBJETO *obj);
