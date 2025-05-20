#include <stdbool.h>

void colision(float *x, float *y, float *xCrate, float *yCrate, int frame, int dir, int w, int h) {
    // Retângulo do personagem
    float px = *x, py = *y;
    float pw = w, ph = h;

    // Retângulo da caixa
    float cx = *xCrate, cy = *yCrate;
    float cw = w, ch = h;

    // Verifica sobreposição
    if (px < cx + cw && px + pw > cx &&
        py < cy + ch && py + ph > cy) {
        // Simples: "empurra" o personagem para fora da caixa dependendo da direção
        if (dir == 0) // baixo
            *y = cy - ph;
        else if (dir == 1) // esquerda
            *x = cx + cw;
        else if (dir == 2) // cima
            *y = cy + ch;
        else if (dir == 3) // direita
            *x = cx - pw;
    }
}