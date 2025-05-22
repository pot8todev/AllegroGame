#pragma once
#include "../structures/objeto.h"
#include <stdbool.h>

void moving_test_up(bool keyTest, bool *moving, OBJETO *obj);
void moving_test_down(bool keyTest, bool *moving, OBJETO *obj);
void moving_test_right(bool keyTest, bool *moving, OBJETO *obj);
void moving_test_left(bool keyTest, bool *moving, OBJETO *obj);
void fps(int *frame_counter, int *frame, int num_frames);
void normal_vetor(OBJETO *obj);
