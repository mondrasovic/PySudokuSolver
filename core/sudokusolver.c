#include <stdio.h>
#include <stdlib.h>

#include "sudokusolver.h"

#define ALL_VALS_BIT_REP 511 // 2^9 - 1

#define N_SUBGRIDS 9

#define EMPTY_CELL 0

typedef unsigned char cell_t;
typedef cell_t grid_t[N_ROWS][N_COLS];

typedef struct _cands_t {
    int rows[N_ROWS];
    int cols[N_COLS];
    int subgrids[N_SUBGRIDS];
} cands_t;

static void str_rep_to_grid(const char *grid_repr_in, grid_t grid)
{
    for (int i = 0; i < GRID_SIZE; ++i) {
        grid[i / N_COLS][i % N_COLS] = grid_repr_in[i] - '0';
    }
}

static void grid_to_str_rep(grid_t grid, char *grid_repr_out)
{
    for (int i = 0; i < GRID_SIZE; ++i)
        grid_repr_out[i] = grid[i / N_COLS][i % N_COLS] + '0';
    grid_repr_out[GRID_SIZE] = '\0';
}

static inline int calc_val_bit(int val)
{
    return 1 << (val - 1);
}

static inline int calc_subgrid_pos(int row, int col)
{
    return (row / 3) * 3 + col / 3;
}
static void candidate_add(int val, int row, int col, cands_t *cands)
{
    int val_bit = calc_val_bit(val);
    cands->rows[row] |= val_bit;
    cands->cols[col] |= val_bit;
    cands->subgrids[calc_subgrid_pos(row, col)] |= val_bit;
}

static void candidate_remove(int val, int row, int col, cands_t *cands)
{
    int rem_val_bits = ~calc_val_bit(val);
    cands->rows[row] &= rem_val_bits;
    cands->cols[col] &= rem_val_bits;
    cands->subgrids[calc_subgrid_pos(row, col)] &= rem_val_bits;
}

static void candidates_init(grid_t grid, cands_t *cands)
{
    for (int i = 0; i < N_ROWS; ++i)
        cands->rows[i] = cands->cols[i] = cands->subgrids[i] = ALL_VALS_BIT_REP;
    
    for (int i = 0; i < N_ROWS; ++i) {
        for (int j = 0; j < N_COLS; ++j) {
            int val = grid[i][j];
            if (val != EMPTY_CELL)
                candidate_remove(val, i, j, cands);
        }
    }
}

static int can_value_be_set(int val, int row, int col, const cands_t *cands)
{
    int all_cands = cands->rows[row] &
        cands->cols[col] &
        cands->subgrids[calc_subgrid_pos(row, col)];
    return (all_cands & calc_val_bit(val)) != 0;
}

static int get_set_bit_if_only_one_in_9_bits(int num)
{
    if (!(num && !(num & (num - 1))))
        return -1;
    int diff = (num & 0x38) - (num & 0x07);
    int shift = (diff < 0) ? 0 : ((diff > 0) ? 3 : 6);
    diff = (num & (0x02 << shift)) - (num & (0x01 << shift));
    return ((diff < 0) ? 0 : ((diff > 0) ? 1 : 2)) + shift;
}

static void solve_fill_certain_cells(grid_t grid, cands_t *cands)
{
    int done;
    do {
        done = 1;
        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < N_COLS; ++j) {
                if (grid[i][j] == EMPTY_CELL) {
                    int common_cands = cands->rows[i] &
                        cands->cols[j] &
                        cands->subgrids[calc_subgrid_pos(i, j)];
                    int bit_pos = get_set_bit_if_only_one_in_9_bits(common_cands);
                    if (bit_pos >= 0) {
                        int val = bit_pos + 1;
                        grid[i][j] = val;
                        candidate_remove(val, i, j, cands);
                        done = 0;
                    }
                }
            }
        }
    } while (!done);
}

static int solve_backtrack(int row, int col, grid_t grid, cands_t *cands)
{
    if (row == N_ROWS)
        return 1;
    
    int next_row = row;
    int next_col = col + 1;
    
    if (next_col == N_COLS) {
        ++next_row;
        next_col = 0;
    }

    if (grid[row][col] == EMPTY_CELL) {
        for (int val = 1; val <= 9; ++val) {
            if (can_value_be_set(val, row, col, cands)) {
                candidate_remove(val, row, col, cands);
                grid[row][col] = val;
                if (solve_backtrack(next_row, next_col, grid, cands))
                    return 1;
                grid[row][col] = EMPTY_CELL;
                candidate_add(val, row, col, cands);
            }
        }
        return 0;
    } else {
        return solve_backtrack(next_row, next_col, grid, cands);
    }
}

int sudoku_solve(const char *grid_repr_in, char *grid_repr_out)
{
    grid_t grid;
    cands_t cands;

    str_rep_to_grid(grid_repr_in, grid);
    candidates_init(grid, &cands);
    solve_fill_certain_cells(grid, &cands);
    if (solve_backtrack(0, 0, grid, &cands)) {
        grid_to_str_rep(grid, grid_repr_out);
        return 1;
    } else {
        return 0;
    }
}
