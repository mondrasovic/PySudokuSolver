#include <ctype.h>
#include <stdio.h>

#include "core/sudokusolver.h"

static void sudoku_print(const char *grid_repr)
{
    for (int i = 0; i < GRID_SIZE; ++i) {
        int col = i % N_COLS;
        printf("%c", grid_repr[i]);
        printf((col == N_COLS - 1) ? "\n" : " ");
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    char grid_repr_in[GRID_REPR_SIZE];
    char grid_repr_out[GRID_REPR_SIZE];

    int i = 0;
    while (i < GRID_SIZE) {
        char val;
        scanf("%c", &val);
        if (isdigit(val)) {
            grid_repr_in[i] = val;
            ++i;
        }
    }
    grid_repr_in[GRID_SIZE] = '\0';

    sudoku_print(grid_repr_in);
    sudoku_solve(grid_repr_in, grid_repr_out);
    printf("************************************\n");
    sudoku_print(grid_repr_out);

    return 0;
}
