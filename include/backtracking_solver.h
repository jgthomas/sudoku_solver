#ifndef BACKTRACKING_SOLVER_H
#define BACKTRACKING_SOLVER_H

bool row_contains(Grid *puzzle, int row, int find);
bool col_contains(Grid *puzzle, int col, int find);
bool box_contains(Grid *puzzle, int min_row, int min_col, int find);
bool num_allowed(Grid *puzzle, int row, int col, int num);
int min_col(Grid *puzzle, int col);
int min_row(Grid *puzzle, int row);
Square *make_square(int num, bool part_of_puzzle);
Grid *make_grid(int grid_size, int grid[grid_size][grid_size]);
bool fill_square(Grid *puzzle, int row, int col);
void solve_puzzle(Grid *puzzle);
void delete_puzzle(Grid *puzzle);

#endif
