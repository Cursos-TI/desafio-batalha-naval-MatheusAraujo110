#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10

int main() {
    int i, j;

    // Tabuleiro 10x10 inicializado com água (0)
    int tabuleiro[LINHAS][COLUNAS] = {0};

    // ===== Navios =====
    // Horizontal
    int linhaH = 2, colunaH = 4;
    for (j = 0; j < 3; j++) {
        if (colunaH + j < COLUNAS && tabuleiro[linhaH][colunaH + j] == 0) {
            tabuleiro[linhaH][colunaH + j] = 3;
        }
    }

    // Vertical
    int linhaV = 5, colunaV = 7;
    for (i = 0; i < 3; i++) {
        if (linhaV + i < LINHAS && tabuleiro[linhaV + i][colunaV] == 0) {
            tabuleiro[linhaV + i][colunaV] = 3;
        }
    }

    // Diagonal ↘ (linha++ coluna++)
    int linhaD1 = 0, colunaD1 = 0;
    for (i = 0; i < 3; i++) {
        if (linhaD1 + i < LINHAS && colunaD1 + i < COLUNAS && tabuleiro[linhaD1 + i][colunaD1 + i] == 0) {
            tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
        }
    }

    // Diagonal ↙ (linha++ coluna--)
    int linhaD2 = 0, colunaD2 = 9;
    for (i = 0; i < 3; i++) {
        if (linhaD2 + i < LINHAS && colunaD2 - i >= 0 && tabuleiro[linhaD2 + i][colunaD2 - i] == 0) {
            tabuleiro[linhaD2 + i][colunaD2 - i] = 3;
        }
    }

    // ===== Imprime tabuleiro =====
    printf("=== Tabuleiro Batalha Naval ===\n\n");
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}