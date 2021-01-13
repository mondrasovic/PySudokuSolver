#include <stdio.h>

#include "core/sudokusolver.h"

static void sudoku_print(grid_t grid)
{
    for (int i = 0; i < N_ROWS; ++i) {
        for (int j = 0; j < N_COLS; ++j) {
            if (j > 0)
                printf(" ");
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    grid_t grid;

    for (int i = 0; i < N_ROWS; ++i) {
        char line[10];
        scanf("%s", line);

        for (int j = 0; j < N_COLS; ++j) {
            int val = line[j] - '0';
            grid[i][j] = val;
        }
    }

    sudoku_print(grid);
    sudoku_solve(grid);
    printf("\n");
    sudoku_print(grid);

    return 0;
}
