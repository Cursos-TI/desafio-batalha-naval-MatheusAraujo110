#include <stdio.h>

int main() {
    int i, j;

    int tabuleiro[10][10] = {0};

    int linhaNavioHorizontal = 2, colunaNavioHorizontal = 4;
    int linhaNavioVertical = 5, colunaNavioVertical = 7;

    for (j = 0; j < 3; j++) {
        tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + j] = 3;
    }

    for (i = 0; i < 3; i++) {
        tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = 3;
    }

    printf("=== Tabuleiro Batalha Naval ===\n\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
