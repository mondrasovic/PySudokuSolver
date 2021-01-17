#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#define GRID_SIZE 81
#define GRID_REPR_SIZE 82

#define N_ROWS 9
#define N_COLS 9

extern int sudoku_solve(const char *grid_repr_in, char *grid_repr_out);

#endif // SUDOKUSOLVER_H
