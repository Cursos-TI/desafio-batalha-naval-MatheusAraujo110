#include <stdio.h>
#include <stdlib.h> // para abs()

#define LINHAS 10
#define COLUNAS 10
#define MAT_SIZE 5 // tamanho fixo das matrizes de habilidade (5x5)

/* Constantes visuais:
   0 -> água
   3 -> navio
   5 -> área afetada pela habilidade
*/

/* Funções para construir as matrizes de habilidade (0/1) */
void build_cone(int mat[MAT_SIZE][MAT_SIZE])
{
    int center = MAT_SIZE / 2; // para MAT_SIZE=5, center=2
    for (int r = 0; r < MAT_SIZE; r++)
    {
        for (int c = 0; c < MAT_SIZE; c++)
        {
            // cone apontando para baixo: linha 0 tem largura 1 no centro,
            // linha 1 largura 3, linha 2 largura 5 (até o centro).
            if (r <= center)
            {
                if (c >= center - r && c <= center + r)
                    mat[r][c] = 1;
                else
                    mat[r][c] = 0;
            }
            else
            {
                // abaixo do centro mantemos sem efeito (0) — isso deixa
                // um cone "triangular" como no exemplo.
                mat[r][c] = 0;
            }
        }
    }
}

void build_cross(int mat[MAT_SIZE][MAT_SIZE])
{
    int center = MAT_SIZE / 2;
    for (int r = 0; r < MAT_SIZE; r++)
    {
        for (int c = 0; c < MAT_SIZE; c++)
        {
            if (r == center || c == center)
                mat[r][c] = 1;
            else
                mat[r][c] = 0;
        }
    }
}

void build_octahedron(int mat[MAT_SIZE][MAT_SIZE])
{
    int center = MAT_SIZE / 2;
    for (int r = 0; r < MAT_SIZE; r++)
    {
        for (int c = 0; c < MAT_SIZE; c++)
        {
            // vista frontal do "octaedro" -> losango: Manhattan distance <= center
            if (abs(r - center) + abs(c - center) <= center)
                mat[r][c] = 1;
            else
                mat[r][c] = 0;
        }
    }
}

/* Sobrepõe a matriz de habilidade ao tabuleiro, centrando no ponto de origem.
   Observação: aqui optamos por NÃO sobrescrever navios (somente marcar água com 5).
   Se quiser que habilidades sobrescrevam navios, altere a condição tab[...] == 0. */
void overlay(int tab[LINHAS][COLUNAS], int mat[MAT_SIZE][MAT_SIZE], int origin_r, int origin_c)
{
    int center = MAT_SIZE / 2;
    for (int r = 0; r < MAT_SIZE; r++)
    {
        for (int c = 0; c < MAT_SIZE; c++)
        {
            if (mat[r][c] == 1)
            {
                int target_r = origin_r - center + r;
                int target_c = origin_c - center + c;
                if (target_r >= 0 && target_r < LINHAS && target_c >= 0 && target_c < COLUNAS)
                {
                    if (tab[target_r][target_c] == 0)
                    { // só marca água
                        tab[target_r][target_c] = 5;
                    }
                }
            }
        }
    }
}

/* Imprime uma matriz MAT_SIZE x MAT_SIZE (usado para mostrar as habilidades) */
void print_mat(int mat[MAT_SIZE][MAT_SIZE])
{
    for (int r = 0; r < MAT_SIZE; r++)
    {
        for (int c = 0; c < MAT_SIZE; c++)
        {
            printf("%d ", mat[r][c]);
        }
        printf("\n");
    }
}

int main()
{
    int i, j;
    int tabuleiro[LINHAS][COLUNAS] = {0};

    // ===== Posicionamento de navios (igual ao seu exemplo original) =====
    // Horizontal
    int linhaH = 2, colunaH = 4;
    for (j = 0; j < 3; j++)
    {
        if (colunaH + j < COLUNAS && tabuleiro[linhaH][colunaH + j] == 0)
        {
            tabuleiro[linhaH][colunaH + j] = 3;
        }
    }

    // Vertical
    int linhaV = 5, colunaV = 7;
    for (i = 0; i < 3; i++)
    {
        if (linhaV + i < LINHAS && tabuleiro[linhaV + i][colunaV] == 0)
        {
            tabuleiro[linhaV + i][colunaV] = 3;
        }
    }

    // Diagonal ↘ (linha++ coluna++)
    int linhaD1 = 0, colunaD1 = 0;
    for (i = 0; i < 3; i++)
    {
        if (linhaD1 + i < LINHAS && colunaD1 + i < COLUNAS && tabuleiro[linhaD1 + i][colunaD1 + i] == 0)
        {
            tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
        }
    }

    // Diagonal ↙ (linha++ coluna--)
    int linhaD2 = 0, colunaD2 = 9;
    for (i = 0; i < 3; i++)
    {
        if (linhaD2 + i < LINHAS && colunaD2 - i >= 0 && tabuleiro[linhaD2 + i][colunaD2 - i] == 0)
        {
            tabuleiro[linhaD2 + i][colunaD2 - i] = 3;
        }
    }

    // ===== Construção das matrizes de habilidade (5x5) =====
    int cone[MAT_SIZE][MAT_SIZE];
    int cruz[MAT_SIZE][MAT_SIZE];
    int octaedro[MAT_SIZE][MAT_SIZE];

    build_cone(cone);
    build_cross(cruz);
    build_octahedron(octaedro);

    // ===== Pontos de origem no tabuleiro (definidos aqui no código) =====
    // Nota: os pontos são as coordenadas onde a matriz será centrada.
    int origin_cone_r = 2, origin_cone_c = 2; // exemplo: centrado em (2,2)
    int origin_cruz_r = 6, origin_cruz_c = 5; // exemplo: centrado em (6,5)
    int origin_octa_r = 4, origin_octa_c = 7; // exemplo: centrado em (4,7)

    // ===== Sobrepõe habilidades ao tabuleiro =====
    overlay(tabuleiro, cone, origin_cone_r, origin_cone_c);
    overlay(tabuleiro, cruz, origin_cruz_r, origin_cruz_c);
    overlay(tabuleiro, octaedro, origin_octa_r, origin_octa_c);

    // ===== Impressão das matrizes das habilidades (para ver os padrões) =====
    printf("=== Matriz: Cone (5x5) ===\n");
    print_mat(cone);
    printf("\n=== Matriz: Cruz (5x5) ===\n");
    print_mat(cruz);
    printf("\n=== Matriz: Octaedro / Losango (5x5) ===\n");
    print_mat(octaedro);

    // ===== Imprime tabuleiro final =====
    printf("\n=== Tabuleiro Batalha Naval (0=agua, 3=navio, 5=area habilidade) ===\n\n");
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
