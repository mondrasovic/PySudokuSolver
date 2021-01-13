#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#define N_ROWS 9
#define N_COLS 9

#define EMPTY_CELL 0

typedef unsigned char cell_t;
typedef cell_t grid_t[N_ROWS][N_COLS];

extern int sudoku_solve(grid_t grid);

#endif // SUDOKUSOLVER_H
